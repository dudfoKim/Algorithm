#include "ListIter.h"

ListIter::ListIter (List * list)
{
	this->list=list;
}
ListIter::~ListIter ()
{

}
	
void ListIter::begin ()
{
	this->curLoc=0;
}
	
bool ListIter::endOfList ()
{
	return(this->curLoc==this->list->size);
}
	
Element ListIter::currentElement ()
{
	return(this->list->body[this->curLoc]);
}
	
void ListIter::next ()
{
	this->curLoc++;
}
Edge ListIter::getElement()
{
	return(this->list->body[this->curLoc]);
}