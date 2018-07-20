#include "Window.h"
#include "gamefunctions.cpp"
#include <iostream>
#include "SDL_image.h"

using std::cout;
using std::endl;

Window::Window()
{
	cout << "Creating null window" << endl;
 	window = NULL;
	screenSurface = NULL;
	renderer = NULL;
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
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			// Create renderer for window
			// Enable/disable VSync here
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
				else
				{
					//Get window surface
					screenSurface = SDL_GetWindowSurface(window);
				}
			}
		}
	}

	return success;
}
bool Window::loadMedia(Texture &background)
{
	bool success = true;

	// Load background image
	if (!background.loadFromFile("Textures/brainy.png", renderer))
	{
		cout << "Unable to load image 'Textures/brainy.png!'" << endl;
		success = false;
	}
	return success;
}

Window::~Window()
{
	cout << "Closing window" << endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	IMG_Quit();
	SDL_Quit();
}

SDL_Window* Window::getWindow()
{
	return window;
}
SDL_Surface* Window::getSurface()
{
	return screenSurface;
}
SDL_Renderer* Window::getRenderer()
{
	return renderer;
}