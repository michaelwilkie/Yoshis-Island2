#include "Elevator.h"

Elevator::Elevator(float x, float y, int width, int height)
	: Interactive(x, y, 0)
{
	this->width = width;
	this->height = height;
	bool started = false;
	speed = 100;
}
Elevator::Elevator(POINT location, int width, int height)
	: Interactive(location, 0)
{
	this->width = width;
	this->height = height;
	bool started = false;
	speed = 100;
}

void Elevator::setSpeed(float s)
{
	speed = s;
}
float Elevator::getSpeed()
{
	return speed;
}

void Elevator::move()
{
	// If I haven't started moving
	if (!started)
		return;
	// If I reached the end of the track
	if (next == nullptr)
	{
		stop();
		return;
	}
	// If I am close enough to my next destination, start towards the one after that
	if (euclidean_distance(loc, next->loc) < 1)
	{
		loc = POINT(next->loc);
		next = next->getNext();
		return;
	}
	// Move distance d along line between elevator location and elevator destination
	// V(x1 - x0, y1 - y0)
	// V/|V| = U
	// (xd,yd) = (x0, y0) + dU

	VECTOR location(loc.x, loc.y);
	VECTOR destination(next->loc.x, next->loc.y);
	VECTOR V(destination - location);

	VECTOR U = getUnitVector(V);
	float d = speed * dt;

	VECTOR newloc = location + U * d;
	loc = POINT(newloc.x, newloc.y);
}
Elevator::~Elevator()
{

}
bool Elevator::isStarted()
{
	return started;
}
void Elevator::startforward()
{
	started = true;
}
void Elevator::startbackward()
{
	started = true;
}
void Elevator::setNextstop(Path_node *p)
{
	next = p;
}
void Elevator::stop()
{
	started = false;
}
