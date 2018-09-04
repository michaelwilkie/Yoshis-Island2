#include "Elevator.h"

Elevator::Elevator(float x, float y, int width, int height)
	: Interactive(x, y, 0)
{
	this->width = width;
	this->height = height;
	bool started = false;
}
Elevator::Elevator(POINT location, int width, int height)
	: Interactive(location, 0)
{
	this->width = width;
	this->height = height;
	bool started = false;
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
	// If I reached the end of the track
	if (next == NULL)
	{
		stop();
	}
	if (euclidean_distance(loc, next->loc) < 1)
	{
		loc = POINT(next->loc);
		next = next->getNext();
	}
	// Move distance d along line between elevator location and elevator destination
	// V(x1 - x0, y1 - y0)
	// V/|V| = U
	// (xd,yd) = (x0, y0) + dU

	VECTOR location(loc.x, loc.y);
	VECTOR destination(next->loc.x, next->loc.y);
	VECTOR V(location - destination);

	VECTOR U = getUnitVector(V);
	float d = speed / dt;

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
void Elevator::stop()
{
	started = false;
}
