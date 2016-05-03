#include "List.h"
#include <stdio.h>



List::List()
{
	this->head=NULL;
	this->length=0;
}
List::~List()
{
	freeLinkedList (this->head);
}

bool List::isEmpty ()
{
	if(this->head==NULL)
	{
		return true;
	}
	return false;
}
bool List::isFull ()
{
	return true;
}
void List::insert (Element e)
{
	Node *temp= NewObject(Node);
	Node *temp2= NewObject(Node);
	int num;

	if(isEmpty())
	{
		temp->item=e;//index를 temp에 넣어줌
		temp->next=NULL;
		this->head=temp;//temp는 NULL을 가리킨다
		this->length++;//ptr=temp
	}
	else
	{
		temp=this->head;
		while(temp->next!=NULL&&temp->next->item<e)
		{
			temp=temp->next;
		}
		if(temp->next==NULL)
		{
			temp2->item=e;
			temp2->next=NULL;
			temp->next=temp2;
			if(temp->item>temp->next->item)
			{
				num=temp->item;
				temp->item=temp->next->item;
				temp->next->item=num;
			}
		}
		else
		{
			temp2->item=e;
			temp2->next=temp->next;
			temp->next=temp2;
			if(temp->item>temp->next->item)
			{
				num=temp->item;
				temp->item=temp->next->item;
				temp->next->item=num;
			}
		}
		this->length++;
	}
}
Element List::deleteMin ()
{
	int temp=this->head->item;
		
	this->head=this->head->next;
	this->length--;
	
	return temp;
}
Element List::deleteMax ()
{
	Node *temp= this->head;
	int tempnum;
	
	if(this->length==1)
	{
		tempnum=this->head->item;
		this->head=NULL;
		this->length--;

		return tempnum;
	}
	
	while(temp->next->next!=NULL)
	{
		temp=temp->next;
	}
	
	tempnum=temp->next->item;
	temp->next=NULL;
	this->length--;
	
	return tempnum;
}
bool List::doesExist (Element e)
{
	Node *temp=this->head;
	int index=0;
	
	if(isEmpty ())
	{
		return false;
	}
	while(temp!=NULL)
	{
		if(temp->item==e)
		{
			return true;
		}
		temp=temp->next;
		index++;
	}
	
	return false;
}

int List::Length ()
{
	return this->length;
}

bool List::isIndexOK (int index)
{
	if(index>=0&&this->length>index)
	{
		return true;
	}
	
	return false;
}

Element List::deleteKth (int K)
{
	int i=0,tempnum=-1;
	Node *temp=this->head;

	if(isIndexOK (K))
	{
		while(i<K-1)
		{
			temp=temp->next;
			i++;
		}
		if(K==0&&this->length==1)
		{	
			tempnum=this->head->item;
			this->head=NULL;
			this->length--;
		}
		else if(K==0&&this->length!=1)
		{
			tempnum=this->head->item;
			while(temp->next->next!=NULL)
			{	
				temp->item=temp->next->item;
				temp=temp->next;
			}
			temp->item=temp->next->item;
			temp->next=NULL;
			this->length--;
		}
		else
		{
			tempnum=temp->next->item;
			temp->next=temp->next->next;
			this->length--;
		}
	}

	return tempnum;
}

void List::reset()
{
	freeLinkedList (this->head);
	this->head=NULL;
	this->length=0;
}

void List::freeLinkedList (Node * node)
{
	if(node->next==NULL)
	{
		free(node);
	}
	else
	{
		node=node->next;
		freeLinkedList(node);
	}
}