#ifndef WINDOW_H
#define WINDOW_H
#include "gameheader.h"
#include "Texture.h"
class Window
{
private:
	SDL_Window	*window;
	SDL_Surface	*screenSurface;
	SDL_Renderer *renderer;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
public:
	SDL_Surface		* getSurface();
	SDL_Window		* getWindow();
	SDL_Renderer	* getRenderer();
	bool init();
	bool loadMedia(Texture &background);
	Window();
	virtual ~Window();
};
#endif
