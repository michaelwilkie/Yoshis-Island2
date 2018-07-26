// This header file should contain includes for basic STL/File I-O
#ifndef GAMEHEADER_H
#define GAMEHEADER_H
#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>
#include <memory>
#include <string>
#include <math.h>
#include "SHAPES.h"
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Entity.h"

using std::vector;
using std::cout;
using std::endl;

int assignEntityID(bool reset)
{
	// Only this function should handle this static variable
	static unsigned int entityid = 0;

	if (reset)
		entityid = 0;

	int result = entityid;
	entityid++;

	return result;
}
SDL_Surface* loadSurface(std::string path, SDL_Surface *surface);
void createEntity(POINT loc, int layer = -1);
float round(float number, int precision);
float approach(float goal, float &current, float delta);
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
bool checkCollision(CIRCLE& a, CIRCLE& b);
bool checkCollision(SDL_Rect a, SDL_Rect b);
float clamp(float val, float clamp);
double distanceSquared(int x1, int y1, int x2, int y2);
bool operator==(Entity &a, Entity &b);
#endif
