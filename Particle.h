#ifndef Particle_H
#define Particle_H

#include "MYSDL_FUNC.h"

class Particle
{
public:
	static const int TOTAL_PARTICLES = 30;
	//Initialize position and animation
	Particle(int x, int y);

	//Shows the particle
	void render();

	//Checks if particle is dead
	bool isDead();

private:
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	//Offsets
	int mPosX, mPosY;

	//Current frame of animation
	int mFrame;

	//Type of particle
	LTexture* mTexture;
};
#endif
