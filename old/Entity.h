/*#ifndef Entity_H
#define Entity_H

#include "MYSDL_FUNC.h"
//#include "LTexture.h"

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
#endif*/