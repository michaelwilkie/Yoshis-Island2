#ifndef GAMEFUNC_H
#define GAMEFUNC_H
#include "gameheader.h"
#include "gameglobals.h"
#include <sstream>
#include "Wall.h"
#include "Elevator.h";
#include <algorithm>

void modifyEntity(Entity *i, std::string key, std::string value);
double distanceSquared(int x1, int y1, int x2, int y2);
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
bool checkCollision(CIRCLE& a, CIRCLE& b);
bool checkCollision(SDL_Rect &a, SDL_Rect &b);
float clamp(float val, float clamp);
bool operator==(Entity &a, Entity &b);

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
ENTTYPE getEntityType(std::string s)
{
	if (s == "entity")
		return ENTTYPE::ENTITY_TYPE;
	if (s == "interactive")
		return ENTTYPE::INTERACTIVE_TYPE;
	if (s == "wall")
		return ENTTYPE::WALL_TYPE;
	if (s == "elevator")
		return ENTTYPE::ELEVATOR_TYPE;
	if (s == "trigger")
		return ENTTYPE::TRIGGER_TYPE;
	if (s == "effect")
		return ENTTYPE::EFFECT_TYPE;
	return ENTTYPE::NULL_ENT_TYPE;
}
KEYVALUE getKeyValue(std::string s)
{
	if (s == "location")
		return KEYVALUE::LOCATION;
	if (s == "dimensions")
		return KEYVALUE::DIMENSIONS;
	if (s == "parent")
		return KEYVALUE::PARENT;
	if (s == "solid")
		return KEYVALUE::SOLID;
	if (s == "width")
		return KEYVALUE::WIDTH;
	if (s == "height")
		return KEYVALUE::HEIGHT;
	if (s == "speed")
		return KEYVALUE::SPEED;
	if (s == "velocity")
		return KEYVALUE::VELOCITY;
	if (s == "gravity")
		return KEYVALUE::GRAVITY;
	if (s == "angle")
		return KEYVALUE::ANGLE;
	if (s == "frame")
		return KEYVALUE::FRAME;
	if (s == "texture")
		return KEYVALUE::TEXTURE;
	return KEYVALUE::NULL_KEYVALUE;
}
vector<std::string> stringsplit(std::string str, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	vector<std::string> result;
	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		result.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	result.push_back(str);
	return result;
}
void consoleCommand(std::string argstr)
{
	// to do:
	//	return string before space
	//	parse the rest based on key:value:key:value...

	std::transform(argstr.begin(), argstr.end(), argstr.begin(), ::tolower);

	vector<std::string> argvect = stringsplit(argstr, " ");
	if (argvect.size() < 1)
	{
		cout << "No command entered" << endl;
		return;
	}
	if (argvect[0] == "create")
	{
		if (argvect.size() < 2)
		{
			cout << "Not enough arguments provided for: " << argvect[0] << endl;
			cout << "Usage: create classname:key:value:key:value....." << endl;
			return;
		}
		argvect = stringsplit(argvect[1], ":");
		ENTTYPE etype = getEntityType(argvect[0]);

		if (etype == ENTTYPE::NULL_ENT_TYPE)
		{
			cout << "Invalid classname:" << argvect[0] << endl;
			return;
		}
		Entity *e = createEntity(POINT(0, 0), 4, etype);
		for (int i = 1; i < argvect.size() - 1; i+=2)
		{
			std::string key = argvect[i];
			std::string value = argvect[i + 1];
			modifyEntity(e, key, value);		
		}
	}
}
void modifyEntity(Entity *i, std::string key, std::string value)
{
	KEYVALUE ktype = getKeyValue(key);
	if (ktype == KEYVALUE::NULL_KEYVALUE)
	{
		cout << "Invalid key: " << key << endl;
		return;
	}
	switch (ktype)
	{
		case KEYVALUE::LOCATION:
		{
			vector<std::string> argvect = stringsplit(value, " ");
			if (argvect.size() < 2 || argvect.size() > 2)
			{
				cout << "Invalid value: " << value << endl;
				cout << "Usage: x y" << endl;
				return;
			}
			POINT p(std::stof(argvect[0]), std::stof(argvect[1]));
			i->loc = p;
			break;
		}
		case KEYVALUE::DIMENSIONS:

			break;
		case KEYVALUE::PARENT:

			break;
		case KEYVALUE::SOLID:

			break;
		case KEYVALUE::WIDTH:

			break;
		case KEYVALUE::HEIGHT:

			break;
		case KEYVALUE::SPEED:

			break;
		case KEYVALUE::VELOCITY:

			break;
		case KEYVALUE::GRAVITY:

			break;
		case KEYVALUE::ANGLE:
			
			break;
		case KEYVALUE::FRAME:

			break;
		case KEYVALUE::TEXTURE:

			break;
	}
	return;
}
// Create entity at POINT in the 'layer'th layer
Entity* createEntity(POINT loc, int layer, ENTTYPE type)
{
	cout << "Created object in ";
	Entity *i = NULL;
	switch (type)
	{
	case ENTTYPE::WALL_TYPE:
		i = new Wall(loc.x, loc.y);
		break;
	case ENTTYPE::ELEVATOR_TYPE:
		i = new Elevator(loc.x, loc.y);
	}

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
	default:
		Layer4.push_back(i); // layer 4 default
		cout << "Layer4" << endl;
		break;
	}
	return i;
}
void deleteEntity(int id)
{
	Layer1.erase(std::remove_if(Layer1.begin(), Layer1.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer1.end());

	Layer2.erase(std::remove_if(Layer2.begin(), Layer2.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer2.end());

	Layer3.erase(std::remove_if(Layer3.begin(), Layer3.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer3.end());

	Layer4.erase(std::remove_if(Layer4.begin(), Layer4.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer4.end());

	Layer5.erase(std::remove_if(Layer5.begin(), Layer5.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer5.end());

	Layer6.erase(std::remove_if(Layer6.begin(), Layer6.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer6.end());

	Layer7.erase(std::remove_if(Layer7.begin(), Layer7.end(),
		[id](Entity *e)
	{
		return e->id == id;
	}), Layer7.end());

	ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(),
		[id](Entity *e)
	{
		bool success = false;
		if (e->id == id)
		{
			success = true;
			delete e;
		}

		return success;
	}), ObjectList.end());
}
float round(float number, int precision)
{
	int e = (pow(10, precision));
	int f = number * e;
	return ((float)f / e);
}
float approach(float goal, float &current, float delta)
{
	float difference = goal - current;

	if (difference >  delta) return current + delta;
	if (difference < -delta) return current - delta;

	return goal;
}
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	for (auto &e : a)
		for (auto &f : b)
			if (!checkCollision(e, f))
				return false;
	
	return true;
}
bool checkCollision(CIRCLE& a, CIRCLE& b)
{
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//If the distance between the centers of the circles is less than the sum of their radii
	return (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared));
}
bool checkCollision(SDL_Rect &a, SDL_Rect &b)
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
VECTOR getUnitVector(VECTOR V)
{
	float d = sqrt(V.x * V.x + V.y * V.y);
	return VECTOR(V.x/d, V.y/d);
}
float clamp(float val, float clamp)
{
	if (abs(val) > abs(clamp))
		if (val < 0)
			return (-clamp);
		else
			return clamp;
	else
		return val;
}
double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}
bool operator==(Entity &a, Entity &b)
{
	return a.id == b.id;
}
float euclidean_distance(POINT a, POINT b)
{
	return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}
#endif