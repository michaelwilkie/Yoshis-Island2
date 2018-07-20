#ifndef GAMEFUNC_H
#define GAMEFUNC_H
#include "gameheader.h"
#include "gameglobals.h"
#include "Interactive.h"


SDL_Surface* loadSurface(std::string path, SDL_Surface *surface)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
// Todo - differentiate type of entities
//		- use arg parse-based differentiation
//		  for instance:
//		  string: "class:interactive:texture:brainy.png:size:50 50:location:10 10:"
//bool createEntity(std::string args)
void createEntity(POINT loc, int layer = -1)
{
	cout << "Created object in ";
	Entity *i = new Interactive(loc);
	ObjectList.push_back(i);
	switch (layer)
	{
	case 1:
		Layer1.push_back(i);
		cout << "Layer1" << endl;
		break;
	case 2:
		Layer2.push_back(i);
		cout << "Layer2" << endl;
		break;
	case 3:
		Layer3.push_back(i);
		cout << "Layer3" << endl;
		break;
	case 4:
		Layer4.push_back(i);
		cout << "Layer4" << endl;
		break;
	case 5:
		Layer5.push_back(i);
		cout << "Layer5" << endl;
		break;
	case 6:
		Layer6.push_back(i);
		cout << "Layer6" << endl;
		break;
	case 7:
		Layer7.push_back(i);
		cout << "Layer7" << endl;
		break;
	case -1:
		Layer3.push_back(i); // layer 3 default
		cout << "Layer3" << endl;
		break;
	}
	return;
}
#endif