#include "VertexQueue.h"



VertexQueue * VertexQueue_new ()
{
	VertexQueue * temp=NewObject(VertexQueue);

	temp->front=NULL;
	temp->rear=NULL;
	temp->length=0;

	return temp;
}
void VertexQueue_free (VertexQueue * _this)
{
	VertexNode *temp1=_this->front;
	

	if(!VertexQueue_isEmpty (_this))
	{
		while(temp1->next!=NULL)
		{
			temp1=_this->front;
			while(temp1->next!=NULL)
			{	
				temp1=temp1->next;
			}
			free(temp1->next);
		}
	}

	free(_this->front);
	free(_this);
}
void VertexQ_add (VertexQueue * _this, Vertex v)
{
	VertexNode *temp=NewObject(VertexNode);
	VertexNode *temp2=NewObject(VertexNode);

	//temp=NULL;
	//temp2=NULL;
	if(VertexQueue_isEmpty(_this))
	{
		
		temp->v=v;
		temp->next=NULL;
		_this->front=temp;
		_this->rear=temp;
	
	}
	else
	{
		
		temp2->v=v;
		temp2->next=_this->front;
		_this->front=temp2;
		
		
	}
	_this->length++;

}
Vertex VertexQueue_delete (VertexQueue * _this)
{
	VertexNode *temp=NewObject(VertexNode);
	Vertex V;

	temp=_this->front;
	
	if(_this->length==1)
	{
		V=_this->front->v;
		
		_this->front=NULL;
		_this->rear=NULL;
		_this->length--;
		return V;
	}


	while(temp->next!=_this->rear)
	{
			temp=temp->next;
	}
	V=_this->rear->v;
	_this->rear=temp;
	_this->rear->next=NULL;
	
	_this->length--;

	return V;
}

Bool VertexQueue_isEmpty (VertexQueue * _this)
{
	if(_this->front==NULL)
	{
		return T;
	}
	return F;
}