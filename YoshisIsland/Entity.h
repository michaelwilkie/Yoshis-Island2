#ifndef ENTITY_H
#define ENTITY_H
#include "SHAPES.h"
#include "gameheader.h"
#include "Texture.h"

using std::vector;
class Entity
{
public:
	Entity(float x = 0, float y = 0, int entid = assignEntityID(false));
	~Entity();

	int id;
	POINT loc;
	vector<SDL_Rect> dim;
	Entity *parent;
	virtual void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;
};
#endif