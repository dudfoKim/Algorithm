#include "Iterator.h"

Iterator * Iterator_new (List * list)
{
	Iterator * _this=NewObject(Iterator);
	_this->list=list;

	return _this;
}

void Iterator_free (Iterator * _this)
{
	free(_this);
}

void Iterator_begin (Iterator * _this)
{
	_this->currentLocation=0;
}

Bool Iterator_endOfList (Iterator * _this)
{
	if(_this->currentLocation==_this->list->length)
	{
		return T;
	}
	return F;
}

Element Iterator_currentElement (Iterator * _this)
{
	return (_this->list->body[_this->currentLocation] ) ;
}

void Iterator_next (Iterator * _this)
{
	_this->currentLocation++;
}