#include <stdlib.h>
#include <stdio.h>
#include "UnsortedLinkedList.h"

struct _Node{
	int data;
	Node * nextnode;
};
struct _UnsortedLinkedList{
	int length;
	Node * head;
};
UnsortedLinkedList * UnsortedLinkedList_new ()
{
	UnsortedLinkedList *temp=NewObject(UnsortedLinkedList);
	temp->head=NULL;
	temp->length=0;
	
	return temp;

}
void UnsortedLinkedList_free (UnsortedLinkedList * _this)
{
	free(_this);//리스트의 배열을 free
}
Bool UnsortedLinkedList_isEmpty (UnsortedLinkedList * _this)
{
	if(_this->head==NULL)
	{
		return T;
	}
	return F;
}
Bool UnsortedLinkedList_isFull (UnsortedLinkedList * _this)
{
	
	return T;
}
void UnsortedLinkedList_insert (UnsortedLinkedList * _this, Element e)
{
	Node *temp= NewObject(Node);
	
	
	if(UnsortedLinkedList_isEmpty(_this))
	{
		
		
			temp->data=e;//index를 temp에 넣어줌
			temp->nextnode=NULL;
			_this->head=temp;//temp는 NULL을 가리킨다
			_this->length++;
			
			//ptr=temp
			
	}
	else if((_this!=NULL)&&UnsortedLinkedList_isFull(_this))
	{	
		temp->data=e;//temp는 ptr을 가리킨다.
		temp->nextnode=_this->head;
		_this->head=temp;

			//temp에 index를 넣어준다.
		_this->length++;
			
		
				;//ptr을 temp위치로 올려준다.
	}
}
Element UnsortedLinkedList_min (UnsortedLinkedList * _this)
{
	Node *temp= _this->head;
	int min, index=0;
	
	min=temp->data;
	
	
	while(temp->nextnode!=NULL)
	{
		if(temp->data<min)
		{
			min=temp->data;
		}
		temp=temp->nextnode;
		index++;
	}

	return min;
		

}
Element UnsortedLinkedList_max (UnsortedLinkedList * _this)
{
	Node *temp= _this->head;
	int max, index=0;
	
	max=temp->data;
	
	while(temp->nextnode!=NULL)
	{
		if(temp->data<max)
		{
			max=temp->data;
		}
		temp=temp->nextnode;
		index++;
	}

	return max;

}
Bool UnsortedLinkedList_search (UnsortedLinkedList * _this, Element key)
{
	Node *temp=_this->head;
	int index=0;
	while(temp!=NULL)
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

