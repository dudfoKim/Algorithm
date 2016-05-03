#include <stdlib.h>
#include <stdio.h>
#include "SortedLinkedList.h"

struct _Node{
	int data;
	Node * nextnode;
};
struct _SortedLinkedList{
	int length;
	Node * head;
};
SortedLinkedList * SortedLinkedList_new ()
{
	SortedLinkedList *temp=NewObject(SortedLinkedList);
	temp->head=NULL;
	temp->length=0;
	
	return temp;

}
void SortedLinkedList_free (SortedLinkedList * _this)
{
	free(_this);//리스트의 배열을 free
}
Bool SortedLinkedList_isEmpty (SortedLinkedList * _this)
{
	if(_this->head==NULL)
	{
		return T;
	}
	return F;
}
Bool SortedLinkedList_isFull (SortedLinkedList * _this)
{
	
	return T;
	
}
void SortedLinkedList_insert (SortedLinkedList * _this, Element e)
{
	Node *temp= NewObject(Node);
	Node *temp2= NewObject(Node);
	Node *temp3= NewObject(Node);
	int tempnum, i=0;
	
	if(SortedLinkedList_isEmpty(_this))
	{
		
			temp->data=e;//index를 temp에 넣어줌
			temp->nextnode=NULL;
			_this->head=temp;//temp는 NULL을 가리킨다
			_this->length++;//ptr=temp
	}
	else
	{
		temp=_this->head;
		while(_this->head->nextnode!=NULL&&_this->head->data>e)
		{
			_this->head=_this->head->nextnode;
		}
		if(_this->head->nextnode==NULL)
		{
			temp2->data=e;
			temp2->nextnode=NULL;
			_this->head->nextnode=temp2;
			_this->head=temp;
		}
		else
		{
			temp2->data=e;
			temp2->nextnode=_this->head->nextnode;
			_this->head->nextnode=temp2;
			_this->head=temp;
		}
	}

	
}
Element SortedLinkedList_min (SortedLinkedList * _this)
{
	
	
	return _this->head->data;
		

}
Element SortedLinkedList_max (SortedLinkedList * _this)
{
	Node *temp= _this->head;
	
	
	
	while(_this->head->nextnode!=NULL)
	{
		
		_this->head=_this->head->nextnode;
		
	}
	_this->head=temp;
	return temp->data;

}
Bool SortedLinkedList_search (SortedLinkedList * _this, Element key)
{
	Node *temp=_this->head;
	int index=0;
	
	while(temp->nextnode!=NULL)
	{
		if(temp->data==key)
		{
			return T;
		}
		temp=temp->nextnode;
		index++;
	}
	return F;

}

