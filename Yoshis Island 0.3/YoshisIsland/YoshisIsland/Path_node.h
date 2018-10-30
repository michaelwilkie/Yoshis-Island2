#ifndef PATH_NODE_H
#define PATH_NODE_H
#include "gameheader.h"
class Path_node
{
public:
	POINT loc;
	Path_node *next = NULL;
	Path_node *prev = NULL;

	void setNext(Path_node *n);
	void setPrev(Path_node *p);
	Path_node *getNext();
	Path_node *getPrev();
	Path_node(float x, float y);
	~Path_node();
};
#endif