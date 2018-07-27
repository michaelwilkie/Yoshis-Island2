#ifndef GLOBALS_H
#define GLOBALS_H
#include "gameheader.h"
#include "Entity.h"

// List of all Entities that exist in the game
vector<Entity*> ObjectList;

// List of entities to be rendered in a certain order
vector<vector<Entity*>> Layers;
vector<Entity*> Layer1; // Front most layer, probably foliage or hud
vector<Entity*> Layer2; // Foreground Layer
vector<Entity*> Layer3; // Foreground layer
vector<Entity*> Layer4; // Center layer, where player and most interactive objects should be.
vector<Entity*> Layer5; // Secondary layer, perhaps an alternate path to take than center layer.
vector<Entity*> Layer6; // Background layer
vector<Entity*> Layer7; // Background layer

#endif