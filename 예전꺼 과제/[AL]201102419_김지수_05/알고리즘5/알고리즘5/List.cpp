#include "List.h"

List::List (int maxSize)
{
	this->maxSize = maxSize ;
	this->size = 0;
	this->body = new Element [maxSize] ;
}

List::~List ()
{
// In reverse order of creation
delete this->body ;
}
bool List::isEmpty ()
{
	if(size==0)
	{
		return true;
	}
	return false;
}

bool List::isFull()
{
	if(size==maxSize)
	{
		return true;
	}
	return false;
}
bool List::insert (Element e)
{
	this->body[size]=e;
	size++;
	return true;
}
int List::getsize()
{
	return size;
}//return size