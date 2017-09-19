#include "Particle.h"

Particle::Particle(int x, int y)
{
	//Set offsets
	mPosX = x - 5 + (rand() % 25);
	mPosY = y - 5 + (rand() % 25);

	//Initialize animation
	mFrame = rand() % 5;

	//Set type
	switch (rand() % 3)
	{
	case 0: mTexture = &gRedTexture; break;
	case 1: mTexture = &gGreenTexture; break;
	case 2: mTexture = &gBlueTexture; break;
	}
}
void Particle::render()
{
	//Show image
	mTexture->render(mPosX, mPosY);

	//Show shimmer
	if (mFrame % 2 == 0)
	{
		gShimmerTexture.render(mPosX, mPosY);
	}
	//Animate
	mFrame++;
}
bool Particle::isDead()
{
	return mFrame > 10;
}