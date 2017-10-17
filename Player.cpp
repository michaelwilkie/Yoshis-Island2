#include "MYSDL_FUNC.h"

Player::Player(int x, int y)
{
	//Initialize the offsets
	mPosX = x;
	mPosY = y;

	//Initialize the velocity
	mVelX = 0;
	mVelY = ENT_VEL;

	velocity.x = 0;
	velocity.y = 0;

	bJump = false;
	jumpflag = false;
	collideflag = false;

	direction = DIR_RIGHT;
	lastdirection = direction;

	gravity.x = 0;
	gravity.y = 5.0;

	//Set collision box dimension
	mCollider.w = ENT_WIDTH;
	mCollider.h = ENT_HEIGHT;

	cCollider.r = ENT_WIDTH / 2;

	//Initialize colliders relative to position
	shiftColliders();
}
Player::Player()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = ENT_VEL;

	velocity.x = 0;
	velocity.y = 0;

	bJump = false;
	jumpflag = false;
	collideflag = false;

	direction = DIR_RIGHT;
	lastdirection = direction;

	gravity.x = 0;
	gravity.y = 5.0;

	//Set collision box dimension
	mCollider.w = ENT_WIDTH;
	mCollider.h = ENT_HEIGHT;

	cCollider.r = ENT_WIDTH / 2;

	//Initialize colliders relative to position
	shiftColliders();
}
void Player::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{

		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:					   break;
		case SDLK_DOWN:  mVelY = ENT_VEL; break;
		case SDLK_LEFT:  mVelX = -ENT_VEL; direction = DIR_LEFT; break;
		case SDLK_RIGHT: mVelX = ENT_VEL; direction = DIR_RIGHT; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:            break;
		case SDLK_DOWN:			break;
		case SDLK_LEFT: mVelX = 0; break;
		case SDLK_RIGHT: mVelX = 0;	break;
		}
	}
}
void Player::move(SDL_Rect& wall)
{
	velocity.x = approach(mVelX, velocity.x, dt * 50);
	velocity.y = approach(mVelY, velocity.y, dt * 5);
	int side = 0;

	mPosX += clamp(velocity.x, ENT_VEL - 2);
	mPosY += clamp(velocity.y, ENT_VEL);

	VECTOR prev(clamp(velocity.x, ENT_VEL - 2), clamp(velocity.y, ENT_VEL)) /*velocity*/;
	mCollider.x = mPosX; mCollider.y = mPosY;

	velocity = velocity + gravity * dt * 5;

	if (checkCollision(mCollider, wall))
	{
		int wallwidth = wall.x + wall.w;
		int collwidth = last.x + last.w;
		if ((last.x < wallwidth && last.x < wall.x && collwidth	< wall.x + 2 && collwidth < wallwidth)
			|| (last.x > wallwidth - 2 && last.x > wall.x && collwidth > wall.x && collwidth > wallwidth))
			side = SIDE;
		else
			side = TOP;

	}
	if (side == TOP)
	{
		_moveY(wall, prev);
		_moveX(wall, prev);
	}
	else
	{
		_moveX(wall, prev);
		_moveY(wall, prev);
	}
	last = mCollider;
}
void Player::_moveX(SDL_Rect& wall, VECTOR& prev)
{
	if (mPosX < 0)
	{
		mPosX = 0;
		mCollider.x = mPosX;
		velocity.x = 0;
	}
	if (mPosX + ENT_WIDTH > LEVEL_WIDTH)
	{
		mPosX = LEVEL_WIDTH - ENT_WIDTH;
		mCollider.x = mPosX;
		velocity.x = 0;
	}
	if (checkCollision(mCollider, wall))
	{
		mPosX -= prev.x;
		mCollider.x = mPosX;
		velocity.x = 0;
	}
}
void Player::_moveY(SDL_Rect& wall, VECTOR& prev)
{
	if (mPosY < 0)
	{
		mPosY = 0;
		mCollider.y = mPosY;
		velocity.y = 0;
	}
	if (checkCollision(mCollider, wall))
	{
		if (mCollider.y + mCollider.h > wall.y)
		{
			//mPosY = wall.y - ENT_HEIGHT;
			mPosY -= prev.y;
			mCollider.y = mPosY;
			velocity.y = 0;
			jumpflag = false;
			bJump = true;
			collideflag = true;
		}
	}
	else
		collideflag = false;
	if (mPosY + ENT_HEIGHT > LEVEL_HEIGHT)
	{
		mPosY = LEVEL_HEIGHT - ENT_HEIGHT;
		velocity.y = 0;
		jumpflag = false;
		bJump = true;
		collideflag = true;
	}

}
void Player::jump()
{
	if (canJump())
	{
		velocity.y -= 50;
		jumpflag = true;
		bJump = false;
	}
	return;
}
void Player::stopJumping()
{
	if (jumpflag && !isFalling())
		velocity.y = -1;
}
bool Player::canJump()
{
	return bJump && collideflag;
}
bool Player::isMoving()
{
	return velocity.x != 0 || velocity.y != 0;
}
bool Player::isFalling()
{
	return velocity.y > 0 && !collideflag /*&& !bJump*/;
}
VECTOR Player::getVelocity()
{
	return velocity;
}
void Player::render(int camX, int camY, Yoshi_Anim e, int frame)
{
	//Show the Player relative to the camera
	if (direction != lastdirection)
	{
		// For some reason it doesn't work with just one flip
		gTexture.render(mPosX - camX, mPosY - camY, &gSpriteClips[e][frame], NULL, NULL, SDL_FLIP_HORIZONTAL);
		gTexture.render(mPosX - camX, mPosY - camY, &gSpriteClips[e][frame], NULL, NULL, SDL_FLIP_HORIZONTAL);
	}
	else
		gTexture.render(mPosX - camX, mPosY - camY, &gSpriteClips[e][frame]);
}
void Player::shiftColliders()
{
	//The row offset
	int r = 0;

	//Center the collision box
	cCollider.x = mPosX + (ENT_WIDTH) / 2;

	//Set the collision box at its row offset
	cCollider.y = mPosY + r;

	//Move the row offset down the height of the collision box

}
Circle& Player::getCollider()
{
	return cCollider;
}
float Player::getPosX()
{
	return mPosX;
}
float Player::getPosY()
{
	return mPosY;
}
Player::~Player()
{}
