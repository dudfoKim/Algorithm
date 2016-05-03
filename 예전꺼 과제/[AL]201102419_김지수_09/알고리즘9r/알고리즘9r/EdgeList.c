#include "EdgeList.h"



EdgeList * EdgeList_new () 
{
		EdgeList *temp=NewObject(EdgeList);
		temp->head=NULL;
		temp->length=0;

}
void EdgeList_free (EdgeList * _this) 
{
	EdgeNode *temp=NewObject(EdgeNode);

	temp=_this->head;

	if(!EdgeList_isEmpty (_this))
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
Bool EdgeList_isEmpty (EdgeList * _this) 
{
	if(_this->head==NULL)
	{
		return T;
	}
	return F;
}
Bool EdgeList_isFull (EdgeList * _this) 
{
	return F;
}
void EdgeList_add (EdgeList * _this, Edge e) 
{
	EdgeNode *temp=NewObject(EdgeNode);
	EdgeNode *temp2=NewObject(EdgeNode);

	if(EdgeList_isEmpty(_this))
	{
		temp->e=e;
		temp->next=NULL;
		_this->head=temp;
	}
	else
	{
		
		temp2->e=e;
		temp2->next=_this->head;
		_this->head=temp2;
	}
	_this->length++;
}