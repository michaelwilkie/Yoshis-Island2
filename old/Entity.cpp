#include "MYSDL_FUNC.h"

Entity::Entity(int x, int y)
{
	//Initialize the offsets
	mPosX = x;
	mPosY = y;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	velocity.x = 0;
	velocity.y = 0;

	collideflag = false;
	frame = 0;

	direction = 0;
	lastdirection = direction;

	gravity.x = 0;
	gravity.y = 0;

	//Set collision box dimension
	mCollider.w = ENT_WIDTH;
	mCollider.h = ENT_HEIGHT;

	cCollider.r = ENT_WIDTH / 2;

	//Initialize colliders relative to position
	shiftColliders();
}
Entity::Entity()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	velocity.x = 0;
	velocity.y = 0;

	collideflag = false;
	frame = 0;

	direction = 0;
	lastdirection = direction;

	gravity.x = 0;
	gravity.y = 0;

	//Set collision box dimension
	mCollider.w = ENT_WIDTH;
	mCollider.h = ENT_HEIGHT;

	cCollider.r = ENT_WIDTH / 2;

	//Initialize colliders relative to position
	shiftColliders();
}
void Entity::handleEvent(SDL_Event& e)
{ }
void Entity::move(SDL_Rect& wall)
{ }

bool Entity::isMoving()
{
	return velocity.x != 0 || velocity.y != 0;
}
VECTOR Entity::getVelocity()
{
	return velocity;
}
void Entity::render(int camX, int camY, int frame)
{
	//Show the Entity relative to the camera
	SDL_Rect entity = { mPosX, mPosY, gTextureWidth, gTextureHeight };
	if (direction != lastdirection)
	{
		// For some reason it doesn't work with just one flip
		gTexture.render(mPosX - camX, mPosY - camY, &entity, NULL, NULL, SDL_FLIP_HORIZONTAL);
		gTexture.render(mPosX - camX, mPosY - camY, &entity, NULL, NULL, SDL_FLIP_HORIZONTAL);
	}
	else
		gTexture.render(mPosX - camX, mPosY - camY, &entity);
}
void Entity::shiftColliders()
{
	//The row offset
	int r = 0;

	//Center the collision box
	cCollider.x = mPosX + (ENT_WIDTH) / 2;

	//Set the collision box at its row offset
	cCollider.y = mPosY + r;
}
Circle& Entity::getCollider()
{
	return cCollider;
}
float Entity::getPosX()
{
	return mPosX;
}
float Entity::getPosY()
{
	return mPosY;
}
Entity::~Entity()
{ }
int Entity::currentFrame()
{
	return frame;
}
bool Entity::isAnimationFinished()
{
	return animcomplete;
}
void Entity::nextFrame()
{
	frame++;
}