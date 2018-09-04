#ifndef GLOBALS_H
#define GLOBALS_H
#include "gameheader.h"
#include "Interactive.h"

// List of all Entities that exist in the game
vector<Interactive*> ObjectList;

// List of entities to be rendered in a certain order
vector<Interactive*> Layer1; // Front most layer, probably foliage or hud
vector<Interactive*> Layer2; // Foreground Layer
vector<Interactive*> Layer3; // Foreground layer
vector<Interactive*> Layer4; // Center layer, where player and most interactive objects should be.
vector<Interactive*> Layer5; // Secondary layer, perhaps an alternate path to take than center layer.
vector<Interactive*> Layer6; // Background layer
vector<Interactive*> Layer7; // Background layer

#endif