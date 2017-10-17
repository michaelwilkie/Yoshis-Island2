#pragma once
#include <SDL.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include "SHAPES.h"
#include "LTimer.h"
//#include "LTexture.h"
//#include "Player.h"
//#include "Particle.h"
#include "Entity.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cmath>
#include <math.h>
enum Yoshi_Anim
{
	YOSHI_IDLE0 = 0,
	YOSHI_IDLE1,
	YOSHI_IDLE2,
	YOSHI_WALK,
	YOSHI_FALL,
	YOSHI_JUMP
};
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Get Texture pointer
	SDL_Texture* getSDLTexture();

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Loads image at specified path
	bool LTexture::loadFromFile(std::string filepath, int filterR, int filterG, int filterB);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};
class Entity
{
public:
	//The dimensions of the dot
	int ENT_WIDTH;
	int ENT_HEIGHT;

	// Maximum velocity of the Entity
	const float ENT_VEL = 5.0;

	//Initializes the variables
	Entity(int x, int y);

	Entity();

	~Entity();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Entity and checks collision
	void move(SDL_Rect& wall);

	bool collideflag;
	//Shows the Entity on the screen relative to the camera
	void render(int camX, int camY, int frame);

	bool isMoving();

	//Position accessors
	float getPosX();
	float getPosY();

	int currentFrame();
	void nextFrame();
	bool isAnimationFinished();

	VECTOR getVelocity();

	//Gets the collision boxes
	//std::vector<SDL_Rect>& getColliders();

	//Gets collision circle
	Circle& getCollider();

	// Texture of Entity
	LTexture gTexture;
	int gTextureWidth;
	int gTextureHeight;

private:
	int direction;
	int frame;
	bool animcomplete;
	int lastdirection;
	float mPosX, mPosY;
	float mVelX, mVelY;
	VECTOR velocity;
	VECTOR gravity;
	//Entity's collision boxes
	SDL_Rect last;
	SDL_Rect mCollider;

	//Entity's collision circle
	Circle cCollider;

	//Moves the collision boxes relative to the Entity's offset
	void shiftColliders();
};

class Player : Entity
{
public:
	//The dimensions of the Player
	static const int ENT_WIDTH = 28;
	static const int ENT_HEIGHT = 28;
	static const int TOP = 1;
	static const int SIDE = 3;
	static const int DIR_LEFT = 0;
	static const int DIR_RIGHT = 1;
	SDL_Rect gSpriteClips[6][10];
	// Maximum velocity of the Entity
	const float ENT_VEL = 5.0;

	//Initializes the variables
	Player(int x, int y);

	Player();

	~Player();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the Entity and checks collision
	void move(SDL_Rect& wall);

	void stopJumping();
	void jump();
	bool canJump();
	bool jumpflag;
	bool collideflag;
	//Shows the Entity on the screen relative to the camera
	void render(int camX, int camY, Yoshi_Anim e, int frame);

	bool isMoving();
	bool isFalling();

	//Position accessors
	float getPosX();
	float getPosY();

	VECTOR getVelocity();

	//Gets the collision boxes
	//std::vector<SDL_Rect>& getColliders();

	//Gets collision circle
	Circle& getCollider();

	// Texture of Entity
	LTexture gTexture;
	int TextureWidth;
	int TextureHeight;

private:

	//Shows the particles
	void renderParticles(int camX, int camY);
	void _moveX(SDL_Rect& wall, VECTOR& prev);
	void _moveY(SDL_Rect& wall, VECTOR& prev);

	int direction;
	int lastdirection;
	float mPosX, mPosY;
	float mVelX, mVelY;
	VECTOR position;
	VECTOR velocity;
	VECTOR gravity;
	bool bJump;
	//Entity's collision boxes
	//std::vector<SDL_Rect> mColliders;
	SDL_Rect last;
	SDL_Rect mCollider;

	//Entity's collision circle
	Circle cCollider;

	//Moves the collision boxes relative to the Entity's offset
	void shiftColliders();
};

// Globals
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface;
extern TTF_Font* gFont;
extern float flCurrentTime;
extern float flPreviousTime;
extern float dt;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern int SCREEN_FPS;
extern int SCREEN_TICKS_PER_FRAME;
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
// End Globals
void MYSDL_setFramerate(int fps);
bool MYSDL_init(bool vsync, SDL_Rect camera);
//bool MYSDL_loadMedia(SDL_Surface** image, std::string filepath);
bool MYSDL_loadMedia(Player &player, int filterR, int filterG, int filterB);
bool checkCollision(SDL_Rect a, SDL_Rect b);
bool checkCollision(Circle& a, Circle& b);
bool checkCollision(Circle& a, SDL_Rect& b);
double distanceSquared(int x1, int y1, int x2, int y2);
SDL_Surface* MYSDL_loadSurface(std::string filepath);
SDL_Texture* MYSDL_loadTexture(std::string filepath);
void MYSDL_close(/*, LTexture &gModulatedTexutre*/);
float clamp(float val, float clamp);
float approach(float goal, float &current, float delta);