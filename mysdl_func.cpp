#include "MYSDL_FUNC.h"
// ************ MYSDL *********************
bool MYSDL_init(bool vsync, SDL_Rect camera)
{
	//Initialization flag
	bool result = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		result = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("2D Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			result = false;
		}
		else
		{
			//Create renderer for window
			if (vsync)
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			else 
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			float scalex = (float)SCREEN_WIDTH / camera.w;
			float scaley = (float)SCREEN_HEIGHT / camera.h;
			printf("Screen dimensions: %dw, %dh\n", SCREEN_WIDTH, SCREEN_HEIGHT);
			printf("Camera dimensions: %dw, %dh\n", camera.w, camera.h);
			printf("Camera Scale: %fx, %fy\n", scalex, scaley);
			SDL_RenderSetScale(gRenderer, scalex, scaley);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				result = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					result = false;
				}
				else
				{
					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						result = false;
					}
					else
					{
						//Initialize SDL_mixer
						if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 8196) < 0)
						{
							printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
							result = false;
						}
					}
				}
			}
		}
	}
	return result;
}
bool MYSDL_loadMedia(SDL_Surface** image, std::string filepath)
{
	//Loading success flag
	bool result = true;

	//Load splash image
	*image = SDL_LoadBMP(filepath.c_str());
	if (*image == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
		result = false;
	}

	return result;
}
bool MYSDL_loadMedia(Entity &player, int filterR, int filterG, int filterB)
{
	bool result = true;
	//Open the font
	gFont = TTF_OpenFont("Fonts/OpenSans-Regular.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed! Too lazy to load font! SDL_ttf Error: %s\n", TTF_GetError());
		result = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

		//Load prompt texture
		if (!player.gTexture.loadFromFile("Textures/yoshisheet2.png", 0, 64, 128))
		{
			printf("Unable to render yoshi texture!\n");
			result = false;
		}
		else
		{
			int xoffset = 1;
			int yoffset = 1;
			int width = 28;
			int height = 32;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					player.gSpriteClips[i][j].x = xoffset + j * width  + j * xoffset;
					player.gSpriteClips[i][j].y = yoffset + i * height + i * yoffset;
					player.gSpriteClips[i][j].w = width;
					player.gSpriteClips[i][j].h = height;
				}
			}
		}
		if (!gRedTexture.loadFromFile("Textures/red.png", filterR, filterG, filterB))
		{
			printf("Unable to render red.png texture!\n");
			result = false;
		}
		if (!gGreenTexture.loadFromFile("Textures/green.png", filterR, filterG, filterB))
		{
			printf("Unable to render green.png texture!\n");
			result = false;
		}
		if (!gBlueTexture.loadFromFile("Textures/blue.png", filterR, filterG, filterB))
		{
			printf("Unable to render blue.png texture!\n");
			result = false;
		}
		if (!gShimmerTexture.loadFromFile("Textures/shimmer.png", filterR, filterG, filterB))
		{
			printf("Unable to render shimmer.png texture!\n");
			result = false;
		}
	}
	//Set texture transparency
	gRedTexture.setAlpha(192);
	gGreenTexture.setAlpha(192);
	gBlueTexture.setAlpha(192);
	gShimmerTexture.setAlpha(192);

	return result;
}
SDL_Surface* MYSDL_loadSurface(std::string filepath)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
		}
				
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	printf("Loaded surface: %s\n", filepath.c_str());
	
	return optimizedSurface;
}
SDL_Texture* MYSDL_loadTexture(std::string filepath)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}	
	return newTexture;
}
void MYSDL_close()
{
	//Free loaded images
	//gPromptTexture.free();

	// Close fonts
	TTF_CloseFont(gFont);

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	return;
}
float approach(float goal, float &current, float delta)
{
	float difference = goal - current;

	if (difference > delta)  return current + delta;
	if (difference < -delta) return current - delta;

	return goal;
}
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Go through the A boxes
	for (int Abox = 0; Abox < a.size(); Abox++)
	{
		//Calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;
		//Go through the B boxes
		for (int Bbox = 0; Bbox < b.size(); Bbox++)
		{
			//Calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				//A collision is detected
				return true;
			}
		}
	}

	//If neither set of collision boxes touched
	return false;
}
bool checkCollision(Circle& a, Circle& b)
{
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//If the distance between the centers of the circles is less than the sum of their radii
	return (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared));
}
bool checkCollision(Circle& a, SDL_Rect& b)
{
	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (a.x < b.x)				cX = b.x;
	
	else if (a.x > b.x + b.w)	cX = b.x + b.w;
	
	else						cX = a.x;	
	//Find closest y offset
	if (a.y < b.y)				cY = b.y;
	
	else if (a.y > b.y + b.h)	cY = b.y + b.h;
	
	else						cY = a.y;
	

	//If the closest point is inside the circle
	return distanceSquared(a.x, a.y, cX, cY) < a.r * a.r;
}
bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}
float clamp(float val, float clamp)
{
	// Clamp the speed to ENT_VEL
	if (abs(val) > abs(clamp))
		if (val < 0)
			return (-clamp);
		else
			return clamp;
	else
		return val;
}
