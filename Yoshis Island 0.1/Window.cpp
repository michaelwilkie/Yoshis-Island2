#include "Window.h"
#include "gamefunctions.cpp"
#include <iostream>

using std::cout;
using std::endl;

Window::Window()
{
	cout << "Creating null window" << endl;
	window = NULL;
	screenSurface = NULL;
	renderer = NULL;
	countedframes = 0;
	VSYNC = true;
	timer.start();
}
float Window::getTime()
{
	return timer.getTicks() / 1000.f;
}
void Window::startFPSTimer()
{
	capTimer.start();
}
void Window::stopFPSTimer()
{
	capTimer.stop();
}
float Window::getFPSTime()
{
	return capTimer.getTicks();
}
int Window::getScreenTicksPerFrame()
{
	return SCREEN_TICKS_PER_FRAME;
}
bool Window::init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("YoshisIsland 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			// Create renderer for window
			// Enable/disable VSync here
			if (VSYNC)
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			else
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}
				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
				else
				{
					//Get window surface
					screenSurface = SDL_GetWindowSurface(window);
				}
			}
		}
	}

	//Open the font
	font = TTF_OpenFont("Fonts/OpenSans-Regular.ttf", 28);
	if (font == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}

	return success;
}
bool Window::loadMedia()
{
	bool success = true;

	for (auto &e : ObjectList)
	{
		if (!e->loadMedia("Textures/brainy.png", renderer, e->loc.x, e->loc.y))
		{
			cout << "Error loading wall texture" << endl;
		}
	}

	return success;
}

Window::~Window()
{
	for (Entity *i : ObjectList)
	{
		delete i;
	}
	cout << "Closing window" << endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	font = NULL;
	renderer = NULL;
	window = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
int Window::getScreenWidth()
{
	return SCREEN_WIDTH;
}
int Window::getScreenHeight()
{
	return SCREEN_HEIGHT;
}
SDL_Window* Window::getWindow()
{
	return window;
}
TTF_Font* Window::getFont()
{
	return font;
}
SDL_Surface* Window::getSurface()
{
	return screenSurface;
}
SDL_Renderer* Window::getRenderer()
{
	return renderer;
}
void Window::calculateAverageFPS()
{
	avgfps = countedframes / getTime();
	if (avgfps > 2000000)
	{
		avgfps = 0;
	}
}