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
Wall::Wall(POINT loc, int w, int h)
	: Interactive(loc, 0.0)
{
	width = w;
	height = h;
	setGravity(VECTOR(0, 0));
}
bool Wall::isSolid()
{
	return solid;
}
void Wall::makeNotsolid()
{
	solid = false;
}
void Wall::makeSolid()
{
	solid = true;
}
void Wall::startforward()
{
	// do nothing, this is a function for the elevator class
}
void Wall::setNextstop(Path_node* p)
{
	// do nothing, this is a function for the elevator class
}
void Wall::move()
{

}
Wall::~Wall()
{

}
