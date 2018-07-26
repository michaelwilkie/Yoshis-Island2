#include "Wall.h"

//
// TO DO:
// Create Wall, make sure you call Entity constructor where appropriate
//

Wall::Wall(float x, float y, int w, int h)
	: Interactive(x, y, 0.0)
{
	width = w;
	height = h;
	setGravity(VECTOR(0, 0));
}
int Wall::getWidth()
{
	return width;
}
int Wall::getHeight()
{
	return height;
}
bool Wall::loadMedia(std::string path, SDL_Renderer *renderer, float x, float y, int width, int height)
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
bool Wall::loadMedia(SDL_Renderer *renderer, float x, float y, int width, int height)
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
bool Wall::isSolid()
{
	return solid;
}
bool Wall::makeNotsolid()
{
	solid = false;
}
bool Wall::makeSolid()
{
	solid = true;
}
Wall::~Wall()
{

}
