
// TODO:
// Take care of circular includes
// then work on Interactive class
#include "gameglobals.h"
#include "Window.h"
#include "Interactive.h"

#ifdef DEBUG
#  define D(x) std::cout << x 
#else
#  define D(x)
#endif // DEBUG

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void ClearScreen(Window &w);
void Render(Window &w);

int assignID(bool reset)
{
	static int id = 0;

	if (reset)
		id = 0;

	int result = id;
	id++;

	return result;
}

int main(int argc, char* args[])
{
	// Main Window
	Window w;

	// Test object - Remove this at some point
	Interactive* i = new Interactive;

	// Event handler
	SDL_Event eventHandler;

	// Modulation components - Remove this at some point
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;

	// Modulation component - Remove this at some point
	Uint8 a = 255;
	double angle = 0.0;

	Layer3.push_back(i);

	if (!w.init())
	{
		cout << "Initialization failed" << endl;
	}
	else
	{
		if (!w.loadMedia(i->getTexture()))
		{
			cout << "Media could not be loaded" << endl;
		}
		else
		{
			bool quit = false;
			i->getTexture().setBlendMode(SDL_BLENDMODE_BLEND);
			// Main game loop
			while (!quit)
			{
				// Event handling loop
				while (SDL_PollEvent(&eventHandler) != 0)
				{
					if (eventHandler.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (eventHandler.type == SDL_KEYDOWN)
					{
						// Increase alpha on w
						if (eventHandler.key.keysym.sym == SDLK_w)
						{
							// Cap if over 255
							if (a + 4 > 255)
							{
								a = 255;
							}
							// Increment otherwise
							else
							{
								a += 4;
								angle += 6;
							}
							cout << "changing alpha and angle" << endl;
							D("changing alpha");
						}
						// Decrease alpha on s
						else if (eventHandler.key.keysym.sym == SDLK_s)
						{
							// Cap if below 0
							if (a - 4 < 0)
							{
								a = 0;
							}
							// Decrement otherwise
							else
							{
								a -= 4;
								angle -= 6;
							}
							cout << "changing alpha and angle" << (int)i->getTexture().getAlpha() << " " << i->getAngle() << endl;
							D("changing alpha");
						}
					}
				}

				// Clear screen
				ClearScreen(w);
				
				i->getTexture().setAlpha(a);
				i->setAngle(angle);

				// Render objects
				Render(w);

				// Show updated screen
				SDL_RenderPresent(w.getRenderer());
			}
		}
	}
	
	return 0;
}
void ClearScreen(Window &w)
{
	SDL_SetRenderDrawColor(w.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(w.getRenderer());
}
void Render(Window &w)
{
	for (auto &ent : Layer1) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
	
	for (auto &ent : Layer2) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
	
	for (auto &ent : Layer3) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
	
	for (auto &ent : Layer4) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
	
	for (auto &ent : Layer5) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
	
	for (auto &ent : Layer6) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
	
	for (auto &ent : Layer7) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());
}