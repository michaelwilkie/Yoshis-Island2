#ifndef GAMEFUNC_H
#define GAMEFUNC_H
#include "gameheader.h"
#include "gameglobals.h"
#include <sstream>
#include "Wall.h"
#include "Elevator.h";
#include <algorithm>

void modifyEntity(Interactive *i, std::string key, std::string value);
double distanceSquared(int x1, int y1, int x2, int y2);
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
bool checkCollision(CIRCLE& a, CIRCLE& b);
bool checkCollision(SDL_Rect &a, SDL_Rect &b);
float clamp(float val, float clamp);
bool operator==(Entity &a, Entity &b);

//////////////////////////////////////////////////////
// This function is from: Lazy Foo's SDL Tutorial   //
// Interface between my code and SDLs library code  //
// Loads an SDL_Surface to a pointer and returns it //
//////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////
// This function is from: Lazy Foo's SDL Tutorial     //
// Interface between my code and SDLs library code    //
// Loads an SDL_Texture into a pointer and returns it //
////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////
// Maps strings to enum ENTTYPE so words                   //
// may be typed into console instead of memorizing numbers //
/////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////
// Maps strings to enum KEYVALUE so words                  //
// may be typed into console instead of memorizing numbers //
/////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////
// Split str into different pieces where delimiter is found //
// They are returned in vector form                         //
//////////////////////////////////////////////////////////////
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
		cout << token << " ";
	}
	result.push_back(str);
	cout << str << endl;
	return result;
}
/////////////////////////////////////////////////////
// Find first delimiter of str                     //
// like stringsplit function but for one iteration //
/////////////////////////////////////////////////////
vector<std::string> stringsplit_first_of(std::string str, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::string token2;

	vector<std::string> result;
	pos = str.find_first_of(delimiter);

	token = str.substr(0, pos);
	token2 = str.substr(pos + delimiter.length(), str.length());

	result.push_back(token);
	result.push_back(token2);

	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////
// To-do: create a first_n like the stringsplit_first_of, but for first n delimiters   //
//                                                                                     //
// Split str into different pieces between delimiters                                  //
// but only the first n delimiters, otherwise the whole string will be split as normal //
/////////////////////////////////////////////////////////////////////////////////////////
vector<std::string> stringsplit_n(std::string str, std::string delimiter, int n)
{
	size_t pos = 0;
	std::string token;
	std::string token2;

	vector<std::string> result;
	pos = str.find_first_of(delimiter);

	token = str.substr(0, pos);
	token2 = str.substr(pos + delimiter.length(), str.length());

	result.push_back(token);
	result.push_back(token2);

	return result;
}
////////////////////////////////////////////////////////////////////////
// Parse console commands                                             //
// So far it is only 'create' and 'setkeyvalue'                       //
// 'create' must be followed by a valid ENTTYPE or classname          //
//  and delimited values for this new entity will be separated by ':' //
//  create classname:key:value:key:value.....                         //
////////////////////////////////////////////////////////////////////////
void consoleCommand(std::string argstr)
{
	// to do:
	//	return string before space
	//	parse the rest based on key:value:key:value...

	std::transform(argstr.begin(), argstr.end(), argstr.begin(), ::tolower);
	cout << argstr << endl;

	vector<std::string> argvect = stringsplit(argstr, " ");
	if (argvect.size() < 1)
	{
		cout << "No command entered" << endl;
		return;
	}
	if (argvect[0] == "create")
	{
		argvect = stringsplit_first_of(argstr, " ");
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
		Interactive *e = createEntity(POINT(0, 0), 4, etype);		

		if (argvect.size() < 2)
			return;

		for (int i = 1; i < argvect.size() - 1; i+=2)
		{
			std::string key = argvect[i];
			std::string value = argvect[i + 1];
			modifyEntity(e, key, value);		
		}
	}
	else if (argvect[0] == "setkeyvalue")
	{
		if (argvect.size() < 3)
		{
			cout << "Not enough arguments provided for: " << argvect[0] << endl;
			cout << "Usage: setkeyvalue id key:value:key:value....." << endl;
			return;
		}
	}
	return;
}
////////////////////////////////////////////////////////////////
// Use Entity* to modify it based on its attributes : key     //
// and the values to change them : value                      //
//                                                            //
// 'key' is converted to KEYVALUE stored in ktype             //
// Entity* will only be modified if ktype is a valid KEYVALUE //
////////////////////////////////////////////////////////////////
void modifyEntity(Interactive *i, std::string key, std::string value)
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
		{
			vector<std::string> argvect = stringsplit(value, " ");
			if (argvect.size() < 2 || argvect.size() > 2)
			{
				cout << "Invalid value: " << value << endl;
				cout << "Usage: x y" << endl;
				return;
			}
			VECTOR v(std::stof(argvect[0]), std::stof(argvect[1]));
			i->setVelocity(v);
			break;
		}
		case KEYVALUE::GRAVITY:
		{
			vector<std::string> argvect = stringsplit(value, " ");
			if (argvect.size() < 2 || argvect.size() > 2)
			{
				cout << "Invalid value: " << value << endl;
				cout << "Usage: x y" << endl;
				return;
			}
			VECTOR g(std::stof(argvect[0]), std::stof(argvect[1]));
			i->setGravity(g);
			break;
		}
		case KEYVALUE::ANGLE:
			try
			{
				i->setAngle(std::stof(value));
			}
			catch (const std::invalid_argument& ia) 
			{
				cout << "Invalid argument exception: " << ia.what() << endl;
			}
			break;
		case KEYVALUE::FRAME:

			break;
		case KEYVALUE::TEXTURE:

			break;
	}
	return;
}
//////////////////////////////////////////////////////////////////////
// Create entity at POINT loc in the layer'th layer of ENTTYPE type //
//////////////////////////////////////////////////////////////////////
Interactive* createEntity(POINT loc, int layer, ENTTYPE type)
{
	Interactive *i = NULL;
	//Entity *e = NULL;
	switch (type)
	{
	case ENTTYPE::WALL_TYPE:
		i = new Wall(loc.x, loc.y);
		break;
	case ENTTYPE::ELEVATOR_TYPE:
		i = new Elevator(loc.x, loc.y);
		break;
	}
	//e = i;
	ObjectList.push_back(i);
	cout << "Created object in ";
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
/////////////////////////////////////////////////////////////////////////////////////////////
// Delete an entity based on its id, and remove it from all layers and from the ObjectList //
/////////////////////////////////////////////////////////////////////////////////////////////
void deleteEntity(int id)
{
	Layer1.erase(std::remove_if(Layer1.begin(), Layer1.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer1.end());

	Layer2.erase(std::remove_if(Layer2.begin(), Layer2.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer2.end());

	Layer3.erase(std::remove_if(Layer3.begin(), Layer3.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer3.end());

	Layer4.erase(std::remove_if(Layer4.begin(), Layer4.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer4.end());

	Layer5.erase(std::remove_if(Layer5.begin(), Layer5.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer5.end());

	Layer6.erase(std::remove_if(Layer6.begin(), Layer6.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer6.end());

	Layer7.erase(std::remove_if(Layer7.begin(), Layer7.end(),
		[id](Interactive *e)
	{
		return e->id == id;
	}), Layer7.end());

	ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(),
		[id](Interactive *e)
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
//////////////////////////////////////////////////////////
// Round number to 'precision' number of decimal places //
//////////////////////////////////////////////////////////
float round(float number, int precision)
{
	int e = (pow(10, precision));
	int f = number * e;
	return ((float)f / e);
}
///////////////////////////////////////////////////////////////
// Starting from 'current', approach 'goal' in 'delta' steps //
// until you've reached the 'goal'                           //
///////////////////////////////////////////////////////////////
float approach(float goal, float &current, float delta)
{
	float difference = goal - current;

	if (difference >  delta) return current + delta;
	if (difference < -delta) return current - delta;

	return goal;
}
//////////////////////////////////////////////////////
// Check collisions between multiple bounding boxes //
//////////////////////////////////////////////////////
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
/////////////////////////////////////
// Returns unit vector of VECTOR V //
/////////////////////////////////////
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
//////////////////////////////////////////////////////////
// Checks if two entities are equal based on their id's //
// and all entities have unique id's                    //
//////////////////////////////////////////////////////////
bool operator==(Entity &a, Entity &b)
{
	return a.id == b.id;
}
///////////////////////////////////////////////////////
// Returns euclidean distance between points a and b //
///////////////////////////////////////////////////////
float euclidean_distance(POINT a, POINT b)
{
	return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}
#endif