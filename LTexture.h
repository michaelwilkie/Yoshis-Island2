#include "MYSDL_FUNC.h"

#ifndef LTexture_H
#define LTexture_H
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Get Texture pointer
	SDL_Texture* getSDLTexture();

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Loads image at specified path
	bool LTexture::loadFromFile(std::string filepath, int filterR, int filterG, int filterB);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};
#endif