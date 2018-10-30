#include "Path_node.h"


void Path_node::setNext(Path_node *n)
{
	next = n;
}
void Path_node::setPrev(Path_node *p)
{
	prev = p;
}
Path_node *Path_node::getNext()
{
	return next;
}
Path_node *Path_node::getPrev()
{
	return prev;
}

Path_node::Path_node(float x, float y)
{
	loc = POINT(x, y);
}


Path_node::~Path_node()
{

}
