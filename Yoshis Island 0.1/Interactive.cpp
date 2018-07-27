#include "Interactive.h"

Interactive::Interactive(float x, float y, double ang)
	: Entity(x, y)
{
	velocity = VECTOR(0, 0);
	gravity = VECTOR(0, 5);
	angle = ang;
}
Interactive::Interactive(POINT location, double ang)
	: Entity(location.x, location.y)
{
	velocity = VECTOR(0, 0);
	gravity = VECTOR(0, 5);
	angle = ang;
}

Interactive::~Interactive()
{

}
double Interactive::getAngle()
{
	return angle;
}
void Interactive::setAngle(double ang)
{
	angle = ang;
}
void Interactive::frameAdvance()
{
	if (frame > FRAMELIMIT)
	{
		frame = -1;
	}
	frame++;
}

void Interactive::setFramelimit(int f)
{
	FRAMELIMIT = f;
	frame = 0;
}
int Interactive::getFramelimit()
{
	return FRAMELIMIT;
}
Texture& Interactive::getTexture()
{
	return texture;
}
void Interactive::render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip)
{
	texture.render(x, y, renderer, clip, angle, center, flip);
}
void Interactive::move()
{
	loc += velocity;
	velocity += gravity;
}
void Interactive::setMaxVelocity(int vel)
{
	MAX_VELOCITY = vel;
}
int Interactive::getMaxVelocity()
{
	return MAX_VELOCITY;
}
VECTOR Interactive::getVelocity()
{
	return velocity;
}
void Interactive::setVelocity(VECTOR v)
{
	velocity = v;
}
VECTOR Interactive::getGravity()
{
	return gravity;
}
void Interactive::setGravity(VECTOR g)
{
	gravity = g;
}