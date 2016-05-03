#include "List.h"

void List_freeLinkedList (List *_this);

List * List_new ()
{
	List *temp=NewObject(List);
	temp->head=NULL;
	temp->length=0;
	
	return temp;

}
void List_free (List * _this)
{
	List_freeLinkedList (_this);
	free(_this->head);//리스트의 배열을 free
}
Bool List_isEmpty (List * _this)
{
	if(_this->head==NULL)
	{
		return T;
	}
	return F;
}
Bool List_isFull (List * _this)
{
	return T;
}
void List_insert (List * _this, Element e)
{
	Node *temp= NewObject(Node);
	Node *temp2= NewObject(Node);
	int num;

	if(List_isEmpty(_this))
	{
		temp->item=e;//index를 temp에 넣어줌
		temp->next=NULL;
		_this->head=temp;//temp는 NULL을 가리킨다
		_this->length++;//ptr=temp
	}
	else
	{
		temp=_this->head;
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
		_this->length++;
	}
}
Element List_deleteMin (List * _this)
{
	int temp=_this->head->item;
		
	_this->head=_this->head->next;
	_this->length--;
	
	return temp;
}
Element List_deleteMax (List * _this)
{
	Node *temp= _this->head;
	int tempnum;
	
	if(_this->length==1)
	{
		tempnum=_this->head->item;
		_this->head=NULL;
		_this->length--;

		return tempnum;
	}
	
	while(temp->next->next!=NULL)
	{
		temp=temp->next;
	}
	
	tempnum=temp->next->item;
	temp->next=NULL;
	_this->length--;
	
	return tempnum;
}
Bool List_doesExist (List * _this, Element e)
{
	Node *temp=_this->head;
	int index=0;
	
	if(List_isEmpty (_this))
	{
		return F;
	}
	while(temp!=NULL)
	{
		if(temp->item==e)
		{
			return T;
		}
		temp=temp->next;
		index++;
	}
	
	return F;
}

int List_length (List * _this)
{
	return _this->length;
}

Bool List_isIndexOK (List * _this, int index)
{
	if(index>=0&&_this->length>index)
	{
		return T;
	}
	
	return F;
}

Element List_deleteKth (List * _this, int K)
{
	int i=0,tempnum=-1;
	Node *temp=_this->head;

	if(List_isIndexOK (_this, K))
	{
		while(i<K-1)
		{
			temp=temp->next;
			i++;
		}
		if(K==0&&_this->length==1)
		{	
			tempnum=_this->head->item;
			_this->head=NULL;
			_this->length--;
		}
		else if(K==0&&_this->length!=1)
		{
			tempnum=_this->head->item;
			while(temp->next->next!=NULL)
			{	
				temp->item=temp->next->item;
				temp=temp->next;
			}
			temp->item=temp->next->item;
			temp->next=NULL;
			_this->length--;
		}
		else
		{
			tempnum=temp->next->item;
			temp->next=temp->next->next;
			_this->length--;
		}
	}

	return tempnum;
}

void List_reset(List * _this)
{
	List_freeLinkedList(_this);
	_this->head=NULL;
	_this->length=0;
}
void List_freeLinkedList (List *_this)
{
	Node *temp=_this->head;
	
	if(!List_isEmpty (_this))
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
}
