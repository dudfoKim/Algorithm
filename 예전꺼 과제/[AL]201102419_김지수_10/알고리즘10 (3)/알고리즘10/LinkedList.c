#include "LinkedList.h"

LinkedList * LinkedList_new () 
{
	LinkedList *temp=NewObject(LinkedList);
	temp->head=NULL;
	temp->rear=NULL;
	temp->length=0;

	return temp;
}

void LinkedList_free (LinkedList * _this) 
{
	Node *temp=NewObject(Node);

	temp=_this->head;

	if(!LinkedList_isEmpty (_this))
	{
		while(temp->next!=NULL)
		{
			temp=_this->head;
			while(temp->next!=NULL)
			{	
				temp=temp->next;
			}
			free(temp->next);
		}
	}
	
	free(_this->head);
}

Bool LinkedList_isEmpty (LinkedList * _this) 
{
	if(_this->length==0)
	{
		
		return T;
	}
	
	return F;
}

Bool LinkedList_isFull (LinkedList * _this) 
{
	return F;
}

void LinkedList_add (LinkedList * _this, Person e) 
{
	Node *temp=NewObject(Node);
	
	if(LinkedList_isEmpty(_this))
	{
		temp->e=e;
		temp->next=NULL;
		_this->head=temp;
		_this->rear=temp;
	}
	
	else
	{
		
		temp->e=e;
		temp->next=_this->head;
		_this->head=temp;
	}
	
	_this->length++;
}

int LinkedList_delete(LinkedList * _this)
{
	int i ;
	
	Node *temp=NewObject(Node);
	temp=_this->head;
	
	if(_this->length==1)
	{
		i=_this->head->e;
		
		_this->head=NULL;
		_this->rear=NULL;
		_this->length--;
		return i;
	}


	while(temp->next!=_this->rear)
	{
			temp=temp->next;
	}
	i=_this->rear->e;
	_this->rear=temp;
	_this->rear->next=NULL;
	
	_this->length--;

	return i;
}

