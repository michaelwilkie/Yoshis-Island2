#ifndef ENTITY_H
#define ENTITY_H
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

	// Interface
	virtual void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;
	virtual bool loadMedia(std::string path, SDL_Renderer *renderer, float x, float y, int width = -1, int height = -1) = 0;
	virtual bool loadMedia(SDL_Renderer *renderer, float x, float y, int width = -1, int height = -1) = 0;
	virtual int getWidth() = 0;
	virtual int getHeight()= 0;
	virtual Texture& getTexture() = 0;
};
#endif