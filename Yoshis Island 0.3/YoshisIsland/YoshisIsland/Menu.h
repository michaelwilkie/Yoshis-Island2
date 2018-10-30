#ifndef MENU_H
#define MENU_H

#include "Window.h"
#include <string>
using std::string;

class Menu
{
public:
	Menu(int scr_width, int scr_height);
	virtual ~Menu();
	Texture titleTexture;
	void render(SDL_Renderer *renderer, TTF_Font *font);

	void setTitle(string s);
	string getTitle();
	
	POINT loc;
	SDL_Rect dim;

	string title;

	SDL_Color txtColor;
	SDL_Color bgColor;
	Uint8 bgAlpha;

	int borderwidth;
	int selected;
	vector<string> items;
};
#endif