#ifndef TEXTURE_H
#define TEXTURE_H
#include "gameheader.h"

class Texture
{
public:
	Texture();
	virtual ~Texture();
	// Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer *renderer);	

	// Renders texture at given point
	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 a);
	
	// Get alpha
	Uint8 getAlpha();

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture * mTexture;

	// Deallocates texture
	void free();

	// Alpha
	Uint8 alpha = 255;

	// Image dimensions
	int width;
	int height;
};
#endif
