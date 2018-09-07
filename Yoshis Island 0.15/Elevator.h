#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Interactive.h"
//#include "Path_node.h"
class Elevator :
	public Interactive
{
public:
	Elevator(float x = 0, float y = 0, int width = -1, int height = -1);
	Elevator(POINT location, int width = -1, int height = -1);
	~Elevator();
	bool isStarted();
	void setSpeed(float s);
	float getSpeed();
	void setNextstop(Path_node *p);
	void move();
	void startforward();
	void startbackward();
	void stop();
private:
	Path_node *next;
	bool started;
	int width;
	int height;
	float speed;
};
#endif