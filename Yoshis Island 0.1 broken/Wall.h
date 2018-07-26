#ifndef WALL_H
#define WALL_H
#include "Interactive.h"
class Wall : public Interactive
{
public:
	Wall(float x = -1, float y = -1, int w = -1, int h = -1);
	bool loadMedia(std::string path, SDL_Renderer *renderer, float x, float y, int width = -1, int height = -1);
	bool loadMedia(SDL_Renderer *renderer, float x, float y, int width = -1, int height = -1);
	int getWidth();
	int getHeight();
	bool isSolid();
	bool makeNotsolid();
	bool makeSolid();
	virtual ~Wall();
private:
	int width;
	int height;
	bool solid;
};
#endif