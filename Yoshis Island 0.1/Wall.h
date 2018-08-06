#ifndef WALL_H
#define WALL_H
#include "Interactive.h"
class Wall : public Interactive
{
public:
	Wall(float x = 0, float y = 0, int w = -1, int h = -1);
	Wall(POINT loc, int w = -1, int h = -1);
	void move();
	bool isSolid();
	void makeNotsolid();
	void makeSolid();
	virtual ~Wall();
private:
	int width;
	int height;
	bool solid;
};
#endif