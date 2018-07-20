#include "MYSDL_FUNC.h"
#include <iomanip>

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Surface* gScreenSurface;
TTF_Font* gFont;
float flCurrentTime;
float flPreviousTime;
float dt;
int SCREEN_HEIGHT = 580;
int SCREEN_WIDTH = 840;
int SCREEN_FPS;
int SCREEN_TICKS_PER_FRAME;
int LEVEL_WIDTH;
int LEVEL_HEIGHT;
void HandleCamera(SDL_Rect& camera, Player& player);

void ClearScreen();

void Update();

void PrintDebugInfo(Player &player, std::stringstream &text, LTexture &gTimeTexture,
	SDL_Color &textColor, int camera_w, int camera_h, double avgFPS);

void Render(LTexture &gBGTexture, Player &player,
	std::stringstream &text, SDL_Rect &camera,
	int frame, Yoshi_Anim yoshianimation);

void HandleInput(Player &player, bool &quit);

void HandleAnimation(Player &player, int &frame, Yoshi_Anim &yoshianimation,
	Yoshi_Anim &test, bool &bOnce, bool &animationcomplete,
	int &animlength);

int main(int argc, char* args[])
{
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };

	int filterR = 0x0;
	int filterG = 0xFF;
	int filterB = 0xFF;	

	//The dot that will be moving around on the screen
	Player player(20,20);
	Entity g(40, 40);

	int frame = 0;
	Yoshi_Anim yoshianimation = YOSHI_IDLE0;
	Yoshi_Anim test = yoshianimation;

	bool animationcomplete = false;
	bool bOnce = true;

	// Collision boxes
	std::vector<SDL_Rect> colliders;

	std::vector<Entity> GlobalEntityList;

	int camera_w = SCREEN_WIDTH / 2;
	int camera_h = SCREEN_HEIGHT / 2;

	//The camera area
	SDL_Rect camera = { 0, 0, camera_w, camera_h };

	float scalex = (float)SCREEN_WIDTH / camera.w;
	float scaley = (float)SCREEN_HEIGHT / camera.h;

	LTexture gYoshi;
	LTexture gBGTexture;
	LTexture gTimeTexture;
	LTexture gFGTexture;

	bool vsync = true;
	bool quit = false;

	int countedFrames = 0;

	LTimer fpsTimer;
	LTimer capTimer;

	int animlength = 8;

	//Set the wall
	SDL_Rect wall = { 0, 700, 460, 120 };

	SDL_Rect visualwall { wall.x, wall.y, wall.w, wall.h };

	std::stringstream text;
	flCurrentTime = 0;
	fpsTimer.start();

	// Initialize SDL
	if (!MYSDL_init(vsync, camera))
	{ }
	else
	{
		if (!MYSDL_loadMedia(player, filterR, filterG, filterB))
		{ }
		else
		{
			gBGTexture.loadFromFile("Textures/1-1.png", filterR, filterG, filterB);
			capTimer.start();
			SDL_QueryTexture(gBGTexture.getSDLTexture(), NULL, NULL, &LEVEL_WIDTH, &LEVEL_HEIGHT);
			SDL_QueryTexture(player.gTexture.getSDLTexture(), NULL, NULL, &player.TextureWidth, &player.TextureHeight);
			while (!quit)
			{
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				flPreviousTime = flCurrentTime;
				flCurrentTime = SDL_GetTicks()/1000.0f;

				dt = flCurrentTime - flPreviousTime;
				if (dt > 0.015f)	dt = 0.015f;

				// Handle keyboard input
				HandleInput(player, quit);
				
				// Handle the animation Yoshi should be doing
				HandleAnimation(player, frame, yoshianimation, test, bOnce, animationcomplete, animlength);

				// Move the dot
				player.move(wall);
				
				// Move camera with respect to player
				HandleCamera(camera, player);

				ClearScreen();

				Render(gBGTexture, player, text, camera, frame, yoshianimation);

				PrintDebugInfo(player, text, gTimeTexture, textColor, camera_w, camera_h, avgFPS);

				Update();
				printf("frame: %d\n", frame / 2);
				//Go to next frame
				++frame;
				
				if (frame / 2 >= animlength)
				{
					//frame = 0;
					animationcomplete = true;
				}

				++countedFrames;
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICKS_PER_FRAME)
				{
					// Wait remaining time
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
				}
			}
		}
	}
	MYSDL_close();

	return 0;
}
void Update()
{
	//Update screen
	SDL_RenderPresent(gRenderer);
}
void Render(LTexture &gBGTexture, Player &player,
		std::stringstream &text	, SDL_Rect &camera,
		int frame				, Yoshi_Anim yoshianimation)		
{
	//Render background
	gBGTexture.render(0, 0, &camera);
	//visualwall.x = wall.x - camera.x;
	//visualwall.y = wall.y - camera.y;
	
	//Render objects
	player.render(camera.x, camera.y, yoshianimation, frame / 4);
}
void HandleCamera(SDL_Rect& camera, Player& player)
{
	//Center the camera over the dot
	camera.x = (player.getPosX() + Player::ENT_WIDTH / 2) - camera.w / 2;
	camera.y = (player.getPosY() + Player::ENT_HEIGHT / 2) - camera.h / 2;

	//Keep the camera in bounds
	if (camera.x < 0)						camera.x = 0;
	if (camera.y < 0)						camera.y = 0;
	if (camera.x > LEVEL_WIDTH - camera.w)	camera.x = LEVEL_WIDTH - camera.w;
	if (camera.y > LEVEL_HEIGHT - camera.h)	camera.y = LEVEL_HEIGHT - camera.h;
}
void ClearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}
void PrintDebugInfo(Player &player, std::stringstream &text, LTexture &gTimeTexture, 
					SDL_Color &textColor, int camera_w, int camera_h, double avgFPS)
{
	text.str("");
	text << "time: " << std::setprecision(2) << std::fixed << flCurrentTime;
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight());
	text.str("");
	text << "ypos: " << player.getPosY();
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 2);
	text.str("");
	text << "xpos: " << player.getPosX();
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 3);
	text.str("");
	text << "vel y: " << player.getVelocity().y;
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 4);
	text.str("");
	text << "vel x: " << player.getVelocity().x;
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 5);
	text.str("");
	text << "fps: " << std::setprecision(2) << std::fixed << avgFPS;
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 6);
	text.str("");
	text << "isFalling: " << player.isFalling() << "jflag: " << player.jumpflag << "cflag: " << player.collideflag;
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 7);
}
void HandleInput(Player &player, bool &quit)
{
	//Event handler
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}
		else if (e.key.keysym.sym == SDLK_SPACE)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
				player.jump();
			if (e.type == SDL_KEYUP)
				player.stopJumping();
		}
		// Handle dot input
		player.handleEvent(e);
	}
}
void HandleAnimation(Player &player, int &frame, Yoshi_Anim &yoshianimation,
					Yoshi_Anim &test, bool &bOnce, bool &animationcomplete,
					int &animlength)
{
	if (player.canJump() && !player.isMoving())
	{
		bOnce = true;
		if (animationcomplete)
		{
			animationcomplete = false;
			frame = 0;
			switch (yoshianimation)
			{
			case YOSHI_IDLE0:
				test = YOSHI_IDLE1;
				break;
			case YOSHI_IDLE1:
				test = YOSHI_IDLE2;
				break;
			case YOSHI_IDLE2:
				test = YOSHI_IDLE0;
				break;
			}
		}
		yoshianimation = test;
	}
	else if (player.canJump() && player.isMoving()) // if player is walking
	{
		bOnce = true;
		if (animationcomplete)
		{
			animationcomplete = false;
			frame = 0;
		}
		yoshianimation = YOSHI_WALK;
	}
	else if (!player.canJump() && player.isMoving() && player.jumpflag) // if player can't jump, has jumped, and is moving
	{
		if (bOnce)
		{
			animationcomplete = false;
			yoshianimation = YOSHI_JUMP;
			bOnce = false;
			frame = 0;
		}
		else
		{
			if (player.isFalling()) // after player has reached peak of jump
			{
				if (yoshianimation == YOSHI_JUMP)
				{
					animationcomplete = false;
					yoshianimation = YOSHI_FALL; // begin to fall
					frame = 3 * animlength;
				}
				else
				{
					if (animationcomplete)
					{
						animationcomplete = false;
						yoshianimation = YOSHI_FALL;
						frame = 2;
						// frame = 8 * animlength
					}
				}
			}
			else
			{
				if (animationcomplete)
				{
					animationcomplete = false;
					frame = 0;
				}
			}
		}
	}
	else if (player.isFalling() && !player.jumpflag)
	{
		if (bOnce)
		{
			animationcomplete = false;
			yoshianimation = YOSHI_FALL;
			bOnce = false;
			frame = 0;
			//frame = 3 * animlength;
		}
		else
		{
			if (animationcomplete)
			{
				animationcomplete = false;
				yoshianimation = YOSHI_FALL;
				frame = 0;
				// frame = 3 * animlength;
			}
		}
	}
}