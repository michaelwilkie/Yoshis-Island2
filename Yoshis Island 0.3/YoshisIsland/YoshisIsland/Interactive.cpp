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
int Interactive::getWidth()
{
	return width;
}
int Interactive::getHeight()
{
	return height;
}
bool Interactive::loadMedia(std::string path, SDL_Renderer *renderer, float x, float y, int width, int height)
{
	bool success = true;
	if (!getTexture().loadFromFile(path, renderer))
	{
		cout << "Error loading file from: " << path << endl;
		success = false;
	}
	if (height == -1 || width == -1)
	{
		SDL_QueryTexture(getTexture().getSDLTexture(), NULL, NULL, &width, &height);
	}
	this->width = width;
	this->height = height;
	SDL_Rect dimensions = { x, y, width, height };

	dim.push_back(dimensions);

	return success;
}
bool Interactive::loadMedia(SDL_Renderer *renderer, float x, float y, int width, int height)
{
	bool success = true;
	if (!getTexture().loadFromFile("Textures/dev_wall.png", renderer))
	{
		cout << "Error loading file from: " << "Textures/dev_wall.png" << endl;
		success = false;
	}
	if (height == -1 || width == -1)
	{
		SDL_QueryTexture(getTexture().getSDLTexture(), NULL, NULL, &width, &height);
	}
	SDL_Rect dimensions = { x, y, width, height };

	dim.push_back(dimensions);

	return success;
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
void Interactive::setSpeed(float s)
{
	speed = s;
}
float Interactive::getSpeed()
{
	return speed;
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
string Interactive::getName()
{
	return name;
}
void Interactive::setName(string n)
{
	name = n;
}