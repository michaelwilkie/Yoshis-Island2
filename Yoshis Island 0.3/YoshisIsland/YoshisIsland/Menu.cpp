#include "Menu.h"

Menu::Menu(int scr_width, int scr_height)
{
	title = "Main Menu";
	dim.w = 200;
	dim.h = 200;
	dim.x = scr_width / 2 - dim.w / 2;
	dim.y = scr_height / 2 - dim.h / 2;
	loc.x = dim.x;
	loc.y = dim.y;
	bgColor  = SDL_Color {0, 0, 0};
	txtColor = SDL_Color{ 255, 0, 255 };
	bgAlpha = 10;
}

Menu::~Menu()
{

}
void Menu::render(SDL_Renderer *renderer, TTF_Font *font)
{
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgAlpha);
	SDL_RenderDrawRect(renderer, &dim);
	//SDL_RenderFillRect(renderer, &dim);
	SDL_SetRenderDrawColor(renderer, txtColor.r, txtColor.g, txtColor.b, bgAlpha);
	if (!titleTexture.loadFromRenderedText(title.c_str(), txtColor, renderer, font))
	{
		cout << "Unable to render avgfps texture!" << endl;
	}
	titleTexture.render(loc.x - (titleTexture.getWidth()/2 - dim.w/2), loc.y + titleTexture.getHeight(), renderer);
}
void Menu::setTitle(string s)
{
	title = s;
}

string Menu::getTitle()
{
	return title;
}
