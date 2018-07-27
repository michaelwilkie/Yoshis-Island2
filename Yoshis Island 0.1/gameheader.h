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
void createEntity(POINT loc, int layer);
float round(float number, int precision);
#endif
