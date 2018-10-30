
// TODO:
// Take care of circular includes
// then work on Interactive class
#include "gameglobals.h"
#include "Menu.h"
#include <sstream>
#include "Path_node.h"
#include <cstdlib>
#include <ctime>
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void ClearScreen(Window &w);
void Render(Window &w);
void Act();
void UpdateScreen(Window &w);

int main(int argc, char* args[])
{
	srand(time(NULL));

	// Main Window
	Window w;

	// Menu enabler
	bool menuenabled = false;

	// Delta time calculation - this should not be removed
	flCurrentTime = 0.0;

	// Test object - Remove this at some point
	Texture TextTexture;
	

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

	// Path Track object - Remove this at some point
	// Remember to also remove the 'delete' statement near the bottom of main
	Path_node *endtrack  = new Path_node(400, 400);
	Path_node *endtrack2 = new Path_node(400,  50);
	Path_node *endtrack3 = new Path_node(50 , 100);
	endtrack->setNext(endtrack2);
	endtrack2->setNext(endtrack3);
	endtrack3->setNext(endtrack);

	// elevator object - Remove this at some point
	Interactive *elevat = nullptr;

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
			Menu mainmenu(w.getScreenWidth(), w.getScreenHeight());
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
							case SDLK_w:
							{
								deleteEntity(0);
								cout << "Deleting an object" << endl;
								break;
							}
							case SDLK_s:
							{
								consoleCommand("create Wall:location:50 50");
								cout << "Creating a wall" << endl;
								cout << "ObjectList size: " << ObjectList.size() << endl;
								w.loadMedia();
								break;
							}
							case SDLK_d:
							{
								int ent_id = consoleCommand("create Elevator:location:50 50:speed:100:");
								elevat = getEntity(ent_id);
								elevat->setNextstop(endtrack);
								elevat->startforward();
								w.loadMedia();
								break;
							}
							case SDLK_f:
							{
								int ent_id = consoleCommand("create Trigger:location:120 120:dimensions:100 100:");
								w.loadMedia();
								break;
							}
							case SDLK_m:
							{
								menuenabled = !menuenabled;
								break;
							}
							case SDLK_ESCAPE:
							{
								quit = true;
								break;
							}
							default:
							{
								// idk
							}
						}
					}
				} // event handling loop
				////////////////////////////
				// Delta time calculation //
				////////////////////////////
				flPreviousTime = flCurrentTime;
				flCurrentTime = SDL_GetTicks()/1000.0f;
				dt = flCurrentTime - flPreviousTime;

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

				
				//////////////////////
				// end time testing //
				//////////////////////

				ClearScreen(w);

				Render(w);
				if (!menuenabled)
					Act();
				else
					mainmenu.render(w.getRenderer(), w.getFont());

				TextTexture.render(0, 0, w.getRenderer());
				// test print - Remove this at some point
				w.renderFPS();

				// Show updated screen
				UpdateScreen(w);

				//Calculate and correct fps
				w.calculateAverageFPS();
			}
		}
	}
	for (Interactive *i : ObjectList)
	{
		delete i;
	}
	delete endtrack;
	delete endtrack2;
	delete endtrack3;

	return 0;
}
void ClearScreen(Window &w)
{
	SDL_SetRenderDrawColor(w.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(w.getRenderer());
}
void Render(Window &w)
{
	SDL_Renderer *renderer = w.getRenderer();
	for (auto &ent : Layer1) ent->render(ent->loc.x, ent->loc.y, renderer);

	for (auto &ent : Layer2) ent->render(ent->loc.x, ent->loc.y, renderer);

	for (auto &ent : Layer3) ent->render(ent->loc.x, ent->loc.y, renderer);

	for (auto &ent : Layer4) ent->render(ent->loc.x, ent->loc.y, renderer);

	for (auto &ent : Layer5) ent->render(ent->loc.x, ent->loc.y, renderer);

	for (auto &ent : Layer6) ent->render(ent->loc.x, ent->loc.y, renderer);

	for (auto &ent : Layer7) ent->render(ent->loc.x, ent->loc.y, renderer);
}

void Act()
{
	for (auto &ent : Layer1) ent->move();

	for (auto &ent : Layer2) ent->move();

	for (auto &ent : Layer3) ent->move();

	for (auto &ent : Layer4) ent->move();

	for (auto &ent : Layer5) ent->move();

	for (auto &ent : Layer6) ent->move();

	for (auto &ent : Layer7) ent->move();
}

void UpdateScreen(Window &w)
{
	SDL_RenderPresent(w.getRenderer());
	return;
}