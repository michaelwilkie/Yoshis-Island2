#ifndef GAMEFUNC_H
#define GAMEFUNC_H
#include "gameheader.h"
#include "gameglobals.h"
#include "Wall.h"

double distanceSquared(int x1, int y1, int x2, int y2);
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
bool checkCollision(CIRCLE& a, CIRCLE& b);
bool checkCollision(SDL_Rect &a, SDL_Rect &b);
float clamp(float val, float clamp);
bool operator==(Entity &a, Entity &b);

SDL_Surface* loadSurface(std::string path, SDL_Surface *surface)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
// Todo - differentiate type of entities
//		- use arg parse-based differentiation
//		  for instance:
//		  string: "class:interactive:texture:brainy.png:size:50 50:location:10 10:"
//bool createEntity(std::string args)
void createEntity(POINT loc, int layer)
{
	cout << "Created object in ";
	Entity *i = new Wall(loc.x, loc.y);
	ObjectList.push_back(i);
	switch (layer)
	{
	case 1:
		Layer1.push_back(i);
		cout << "Layer1" << endl;
		break;
	case 2:
		Layer2.push_back(i);
		cout << "Layer2" << endl;
		break;
	case 3:
		Layer3.push_back(i);
		cout << "Layer3" << endl;
		break;
	case 4:
		Layer4.push_back(i);
		cout << "Layer4" << endl;
		break;
	case 5:
		Layer5.push_back(i);
		cout << "Layer5" << endl;
		break;
	case 6:
		Layer6.push_back(i);
		cout << "Layer6" << endl;
		break;
	case 7:
		Layer7.push_back(i);
		cout << "Layer7" << endl;
		break;
	case -1:
		Layer3.push_back(i); // layer 3 default
		cout << "Layer3" << endl;
		break;
	}
	return;
}
float round(float number, int precision)
{
	int e = (pow(10, precision));
	int f = number * e;
	return ((float)f / e);
}
float approach(float goal, float &current, float delta)
{
	float difference = goal - current;

	if (difference >  delta) return current + delta;
	if (difference < -delta) return current - delta;

	return goal;
}
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	for (auto &e : a)
		for (auto &f : b)
			if (!checkCollision(e, f))
				return false;
	
	return true;
}
bool checkCollision(CIRCLE& a, CIRCLE& b)
{
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//If the distance between the centers of the circles is less than the sum of their radii
	return (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared));
}
bool checkCollision(SDL_Rect &a, SDL_Rect &b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
float clamp(float val, float clamp)
{
	if (abs(val) > abs(clamp))
		if (val < 0)
			return (-clamp);
		else
			return clamp;
	else
		return val;
}
double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}
bool operator==(Entity &a, Entity &b)
{
	return a.id == b.id;
}
#endif