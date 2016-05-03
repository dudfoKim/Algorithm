#include "ListIterator.h"

ListIterator * ListIterator_new (IntervalList * list)
{
	ListIterator * temp = NewObject(ListIterator);
	temp->list=list;
	temp->currentLocation=NULL;

	return temp;

}
void ListIterator_free (ListIterator * _this)
{
	while(!ListIterator_end(_this))
	{
		free(_this);
		ListIterator_next(_this);
	}
}
void ListIterator_begin (ListIterator * _this)
{
	_this->currentLocation=_this->list->head;
}
Bool ListIterator_end (ListIterator * _this)
{
	if(_this->currentLocation==NULL)
	{
		return T;
	}
	return F;
}

int ListIterator_currentElement (ListIterator * _this)
{
	return (_this->currentLocation->e);
}
void ListIterator_next (ListIterator * _this)
{
	_this->currentLocation=_this->currentLocation->next;
}