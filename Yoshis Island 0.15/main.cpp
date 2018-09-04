
// TODO:
// Take care of circular includes
// then work on Interactive class
#include "gameglobals.h"
#include "Window.h"
#include <sstream>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void ClearScreen(Window &w);
void Render(Window &w, Texture &TextTexture);

int main(int argc, char* args[])
{
	// Main Window
	Window w;

	// Test object - Remove this at some point
	Texture TextTexture;
	Texture AVGFPSTexture;

	// Event handler
	SDL_Event eventHandler;

	// Modulation components - Remove this at some point
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;

	// Modulation component - Remove this at some point
	Uint8 a = 255;
	double angle = 0.0;
	std::stringstream fps_str;

	//createEntity(POINT(0, 0), 3, ENTTYPE::WALL_TYPE);
	//createEntity(POINT(w.getScreenHeight()/2, 0), 3, ENTTYPE::WALL_TYPE);
	//createEntity(POINT(0, 0), 4, ENTTYPE::ELEVATOR_TYPE);
	if (!w.init())
	{
		cout << "Initialization failed" << endl;
	}
	else
	{
		if (!w.loadMedia())
		{
			cout << "Media could not be loaded" << endl;
		}
		else
		{
			SDL_Color textcolor = { 0, 0, 0 };
			if (!TextTexture.loadFromRenderedText("Test", textcolor, w.getRenderer(), w.getFont()))
			{
				cout << "Could not load text texture" << endl;
			}
			bool quit = false;

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
						switch (eventHandler.key.keysym.sym)
						{
							// Increase alpha on w
							case SDLK_w:
							{
								deleteEntity(0);
								cout << "Deleting an object" << endl;
								break;
							}
							// Decrease alpha on s
							case SDLK_s:
							{
								consoleCommand("create Wall:location:50 50");
								cout << "Creating a wall" << endl;
								cout << "ObjectList size: " << ObjectList.size() << endl;
								w.loadMedia();
							}
							case SDLK_d:
							{
								consoleCommand("create Elevator:location:50 50");
								w.loadMedia();
							}
						}
					}
				} // event handling loop

				//////////////////
				// Time testing //
				//////////////////
				fps_str.str("");
				float time = round(w.getTime(), 1);
				if (time - (int)time == 0)
					fps_str << "Time: " << (int)time << ".0";
				else
					fps_str << "Time: " << time;
				//Render text
				if (!TextTexture.loadFromRenderedText(fps_str.str().c_str(), textcolor, w.getRenderer(), w.getFont()))
				{
					cout << "Unable to render time texture!" << endl;
				}
				fps_str.str("");
				fps_str << w.avgfps;
				if (!AVGFPSTexture.loadFromRenderedText(fps_str.str().c_str(), textcolor, w.getRenderer(), w.getFont()))
				{
					cout << "Unable to render avgfps texture!" << endl;
				}
				//////////////////////
				// end time testing //
				//////////////////////

				// Clear screen
				ClearScreen(w);

				w.avgfps = w.countedframes / w.getTime();

				// Render objects
				Render(w, TextTexture);
				AVGFPSTexture.render(w.getScreenWidth() - AVGFPSTexture.getWidth(), w.getScreenHeight() / 2, w.getRenderer());
				// Show updated screen
				SDL_RenderPresent(w.getRenderer());

				//Calculate and correct fps
				w.calculateAverageFPS();
				w.countedframes++;
			}
		}
	}
	for (Interactive *i : ObjectList)
	{
		delete i;
	}
	return 0;
}
void ClearScreen(Window &w)
{
	SDL_SetRenderDrawColor(w.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(w.getRenderer());
}
void Render(Window &w, Texture &TextTexture)
{
	//static Entity* obj = Layer3[0];

	for (auto &ent : Layer1) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	for (auto &ent : Layer2) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	for (auto &ent : Layer3) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	for (auto &ent : Layer4) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	for (auto &ent : Layer5) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	for (auto &ent : Layer6) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	for (auto &ent : Layer7) ent->render(ent->loc.x, ent->loc.y, w.getRenderer());

	//TextTexture.render(x - TextTexture.getWidth(), y /*+ TextTexture.getHeight()*/, w.getRenderer());
}