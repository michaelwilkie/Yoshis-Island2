#include "MYSDL_FUNC.h"
#include <iomanip>

void HandleCamera(SDL_Rect& camera, Entity& player);

void ClearScreen();

void Update();

void PrintDebugInfo(Entity &player, std::stringstream &text, LTexture &gTimeTexture,
	SDL_Color &textColor, int camera_w, int camera_h, double avgFPS);

void Render(LTexture &gBGTexture, Entity &player,
	std::stringstream &text, SDL_Rect &camera,
	int frame, Yoshi_Anim yoshianimation);

void HandleInput(Entity &player, bool &quit);

void HandleAnimation(Entity &player, int &frame, Yoshi_Anim &yoshianimation,
	bool &bOnce, bool &animationcomplete,
	int &animlength);

int main(int argc, char* args[])
{
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };

	int filterR = 0x0;
	int filterG = 0xFF;
	int filterB = 0xFF;	

	//The dot that will be moving around on the screen
	Entity player(20,20);

	int frame = 0;
	Yoshi_Anim yoshianimation = YOSHI_IDLE0;

	bool animationcomplete = false;
	bool bOnce = true;

	// Collision boxes
	std::vector<SDL_Rect> colliders;

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
	SDL_Rect wall;
	wall.x = 0;
	wall.y = 700;
	wall.w = 460;
	wall.h = 120;

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
			SDL_QueryTexture(player.gTexture.getSDLTexture(), NULL, NULL, &player.gTextureWidth, &player.gTextureHeight);
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
				HandleAnimation(player, frame, yoshianimation, bOnce, animationcomplete, animlength);

				// Move the dot
				player.move(wall);
				
				// Move camera with respect to player
				HandleCamera(camera, player);

				ClearScreen();

				Render(gBGTexture, player, text, camera, frame, yoshianimation);

				PrintDebugInfo(player, text, gTimeTexture, textColor, camera_w, camera_h, avgFPS);

				Update();
				//printf("Current Animation: %s frame %d\n", (yoshianimation == YOSHI_IDLE0 ? "YOSHI_IDLE0" : "YOSHI_WALK"), frame/8);
				//Go to next frame
				++frame;
				
				if (frame / 8 >= animlength)
				{
					frame = 0;
					//animationcomplete = true;
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
void Render(LTexture &gBGTexture, Entity &player,
		std::stringstream &text	, SDL_Rect &camera,
		int frame				, Yoshi_Anim yoshianimation)		
{
	//Render background
	gBGTexture.render(0, 0, &camera);
	//visualwall.x = wall.x - camera.x;
	//visualwall.y = wall.y - camera.y;
	
	//Render objects
	player.render(camera.x, camera.y, yoshianimation, frame / 8);
}
void HandleCamera(SDL_Rect& camera, Entity& player)
{
	//Center the camera over the dot
	camera.x = (player.getPosX() + Entity::ENT_WIDTH / 2) - camera.w / 2;
	camera.y = (player.getPosY() + Entity::ENT_HEIGHT / 2) - camera.h / 2;

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
void PrintDebugInfo(Entity &player, std::stringstream &text, LTexture &gTimeTexture, 
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
	text << "isFalling: " << player.isFalling() << "jumpflag: " << player.jumpflag << "collideflag: " << player.collideflag;
	gTimeTexture.loadFromRenderedText(text.str().c_str(), textColor);
	gTimeTexture.render(camera_w - gTimeTexture.getWidth(), camera_h - gTimeTexture.getHeight() * 7);
}
void HandleInput(Entity &player, bool &quit)
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
		else if (e.key.keysym.sym == SDLK_e)
		{
			player.HideParticles();
		}
		else if (e.key.keysym.sym == SDLK_r)
		{
			player.ShowParticles();
		}
		// Handle dot input
		player.handleEvent(e);
	}
}
void HandleAnimation(Entity &player, int &frame, Yoshi_Anim &yoshianimation,
					bool &bOnce, bool &animationcomplete,
					int &animlength)
{
	if (player.canJump() && !player.isMoving())
	{
		bOnce = true;
		if (animationcomplete)
		{
			animationcomplete = false;
			frame = 0;
		}
		yoshianimation = YOSHI_IDLE0;
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
					frame = 0;
				}
				else
				{
					if (animationcomplete)
					{
						animationcomplete = false;
						yoshianimation = YOSHI_FALL;
						frame = 3;
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
			frame = 3;
		}
		else
		{
			if (animationcomplete)
			{
				animationcomplete = false;
				yoshianimation = YOSHI_FALL;
				frame = 3;
			}
		}
	}
}