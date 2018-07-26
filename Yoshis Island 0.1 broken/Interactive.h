#ifndef Interactive_H
#define Interactive_H
#include "Entity.h"
#include "Texture.h"

class Interactive :	public Entity
{
public:
	Interactive(POINT location, double ang = 0.0);
	Interactive(float x = 0, float y = 0, double ang = 0.0);
	virtual ~Interactive();
	void frameAdvance();
	void setFramelimit(int f);
	int getFramelimit();
	double getAngle();
	void setAngle(double ang);
	Texture& getTexture();
	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void move();
	void setMaxVelocity(int vel);
	int getMaxVelocity();
	VECTOR getVelocity();
	void setVelocity(VECTOR v);
	VECTOR getGravity();
	void setGravity(VECTOR g);
private:
	int MAX_VELOCITY = 400;
	double angle;
	VECTOR velocity;
	VECTOR gravity;
	int frame;
	int FRAMELIMIT;
	Texture texture;
	vector<SDL_Rect> spriteTable;
};
#endif
