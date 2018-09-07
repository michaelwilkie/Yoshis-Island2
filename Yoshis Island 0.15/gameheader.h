// This header file should contain includes for basic STL/File I-O
#ifndef GAMEHEADER_H
#define GAMEHEADER_H
#include <vector>
#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SHAPES.h"

using std::vector;
using std::unique_ptr;
using std::cout;
using std::endl;

float dt;
float flCurrentTime;
float flPreviousTime;
class Interactive;

enum ENTTYPE
{
	ENTITY_TYPE = 0,
	INTERACTIVE_TYPE,
	WALL_TYPE,
	ELEVATOR_TYPE,
	TRIGGER_TYPE,
	EFFECT_TYPE,
	NULL_ENT_TYPE
};
enum KEYVALUE
{
	LOCATION = 0,
	DIMENSIONS,
	PARENT,
	SOLID,
	WIDTH,
	HEIGHT,
	SPEED,
	VELOCITY,
	GRAVITY,
	ANGLE,
	FRAME,
	TEXTURE,
	NULL_KEYVALUE
};
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
void consoleCommand(std::string argstr);
float euclidean_distance(POINT a, POINT b);
VECTOR getUnitVector(VECTOR V);
Interactive* createEntity(POINT loc, int layer, ENTTYPE type);
float round(float number, int precision);
void deleteEntity(int id);
#endif
