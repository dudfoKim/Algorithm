#include "Iterator.h"



Iterator * Iterator_new (List * list)
{
	Iterator * _this = NewObject(Iterator) ;
	_this->list = list ;

	return _this ;
}

void Iterator_free (Iterator * _this)
{
	free(_this->currentLocation);
	free(_this);
}
void Iterator_begin (Iterator * _this)
{
	_this->currentLocation = _this->list->head ;
}
Bool Iterator_endOfList (Iterator * _this)
{
	if(_this->currentLocation == NULL)
	{
		return T;
	}
	return F;
}
Element Iterator_currentElement (Iterator * _this)
{
	return _this-> currentLocation->item ;
}
void Iterator_next (Iterator * _this)
{
	_this-> currentLocation =_this->currentLocation->next;
}