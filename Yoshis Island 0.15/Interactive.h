#ifndef Interactive_H
#define Interactive_H
#include "Entity.h"
#include "Texture.h"
#include "Path_node.h"
#include <string>

using std::string;

class Interactive : public Entity
{
public:
	Interactive(POINT location, double ang = 0.0);
	Interactive(float x = 0, float y = 0, double ang = 0.0);
	virtual ~Interactive();
	bool loadMedia(std::string path, SDL_Renderer *renderer, float x, float y, int width = -1, int height = -1);
	bool loadMedia(SDL_Renderer *renderer, float x, float y, int width = -1, int height = -1);
	int getWidth();
	int getHeight();
	void frameAdvance();
	void setFramelimit(int f);
	int getFramelimit();
	double getAngle();
	void setAngle(double ang);
	Texture& getTexture();
	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	virtual void move() = 0;
	void setMaxVelocity(int vel);
	int getMaxVelocity();
	VECTOR getVelocity();
	void setVelocity(VECTOR v);
	VECTOR getGravity();
	void setGravity(VECTOR g);
	string getName();
	void setName(string n);
	virtual void setNextstop(Path_node *p) = 0; // For elevator class
	virtual void startforward() = 0; // For elevator class

private:
	int width, height;
	int MAX_VELOCITY = 400;
	double angle;
	VECTOR velocity;
	VECTOR gravity;
	int frame;
	int FRAMELIMIT;
	Texture texture;
	string name;
	vector<SDL_Rect> spriteTable;
};
#endif
