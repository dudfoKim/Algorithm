#include "Iterator.h"

Iter::Iter (List * list)
{
	this->list = list ;
}


void Iter::begin ()
{
	this->currentLocation = this->list->head ;
}
Element Iter::currentElement ()
{
	return this->currentLocation->item ;
}
void Iter::next ()
{
	this->currentLocation = (this->currentLocation)->next ;
}
bool Iter::endOfList ()
{
	return (this->currentLocation == NULL) ;
}