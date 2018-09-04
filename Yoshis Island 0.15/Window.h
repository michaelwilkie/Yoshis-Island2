#ifndef WINDOW_H
#define WINDOW_H
#include "gameheader.h"
#include "Texture.h"
#include "Timer.h"
class Window
{
private:
	SDL_Window * window;
	SDL_Surface	 *screenSurface;
	SDL_Renderer *renderer;
	TTF_Font	 *font;
	Timer timer;
	Timer capTimer;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	int SCREEN_FPS = 60;
	int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	bool VSYNC;
public:
	SDL_Surface * getSurface();
	SDL_Window		* getWindow();
	SDL_Renderer	* getRenderer();
	TTF_Font		* getFont();
	float getTime();
	int getScreenWidth();
	int getScreenHeight();
	void startFPSTimer();
	void stopFPSTimer();
	float getFPSTime();
	int getScreenTicksPerFrame();
	bool init();
	bool loadMedia();
	Window();
	virtual ~Window();
	void calculateAverageFPS();
	float avgfps;
	int countedframes;
};
#endif
