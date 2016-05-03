#include "IntervalList.h"

IntervalList * IntervalList_new ()
{
	IntervalList * temp=NewObject(IntervalList);

	temp->head=NULL;
	temp->length=0;
}
void IntervalList_free (IntervalList * _this)
{
	free(_this);
}
void IntervalList_add (IntervalList * _this, int input)
{
	Node *temp=NewObject(Node);
	

	if(!(_this->length))
	{
		temp->e=input;
		temp->next=NULL;
		_this->head=temp;
	}
	else
	{
		
		temp->e=input;
		temp->next=_this->head;
		_this->head=temp;
	}
	_this->length++;
}