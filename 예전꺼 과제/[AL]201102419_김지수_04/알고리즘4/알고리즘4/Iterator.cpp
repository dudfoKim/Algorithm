#include "Iterator.h"

Iter::Iter (List * list)
{
	this->list = list ;
	
}



void Iter::begin ()
{
	this->currentLocation=0;
}

bool Iter::endOfList ()
{
	return (this->currentLocation==this->list->length) ;
}

Element Iter::currentElement ()
{
	return (this->list->body[this->currentLocation] ) ;
}

void Iter::next ()
{
	this->currentLocation++;
}