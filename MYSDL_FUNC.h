#pragma once
#include <SDL.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include "LTimer.h"
#include "LTexture.h"
#include "Particle.h"
#include "Entity.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cmath>
#include <math.h>

class LTexture;
class Entity;
class Particle;
struct Circle;

// Globals
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Surface* gScreenSurface;
TTF_Font* gFont;
LTexture gRedTexture;
LTexture gBlueTexture;
LTexture gGreenTexture;
LTexture gShimmerTexture;
float flCurrentTime;
float flPreviousTime;
float dt;
int SCREEN_HEIGHT = 580;
int SCREEN_WIDTH = 840;
int SCREEN_FPS;
int SCREEN_TICKS_PER_FRAME;
int LEVEL_WIDTH;
int LEVEL_HEIGHT;
// End Globals
void MYSDL_setFramerate(int fps);
bool MYSDL_init(bool vsync, SDL_Rect camera);
//bool MYSDL_loadMedia(SDL_Surface** image, std::string filepath);
bool MYSDL_loadMedia(Entity &player, int filterR, int filterG, int filterB);
bool checkCollision(SDL_Rect a, SDL_Rect b);
bool checkCollision(Circle& a, Circle& b);
bool checkCollision(Circle& a, SDL_Rect& b);
double distanceSquared(int x1, int y1, int x2, int y2);
SDL_Surface* MYSDL_loadSurface(std::string filepath);
SDL_Texture* MYSDL_loadTexture(std::string filepath);
void MYSDL_close(/*, LTexture &gModulatedTexutre*/);
float clamp(float val, float clamp);
float approach(float goal, float &current, float delta);
