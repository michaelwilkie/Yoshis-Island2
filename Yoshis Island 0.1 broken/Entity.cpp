#include "Entity.h"

Entity::Entity(float x, float y, int entid)
{
	loc = POINT(x, y);
	parent = NULL;
	id = entid;
}
Entity::~Entity()
{

}
