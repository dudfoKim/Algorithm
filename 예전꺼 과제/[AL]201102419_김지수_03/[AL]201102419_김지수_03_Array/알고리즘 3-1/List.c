#include <stdlib.h>
#include <stdio.h>
#include "List.h"

List* List_new(int maxSize)
{
	List* temp=NewObject(List);//새로운 리스트 동적선언
	int i=0;
	
	temp->maxLength=maxSize;//최대 길이를 최대 사이즈로 
	temp->length=0;//원소초기개수는 0개 
	temp->body=NewVector(int ,maxSize);//배열 동적할당

	while(i<maxSize)
	{
		temp->body[i++]=0;//배열값 초기화
	}

	return temp;//생성된 리스트 반환
}

void List_insert(List* _this, int element)
{
	int i=_this->length-1;
	
	if(List_isFull(_this))
	{
		printf("List FULL!");
	}
	else if(i==-1)
	{
		_this->body[i+1]=element;
		_this->length++;
	}
	else
	{
		while((i>-1)&&(_this->body[i]>=element))
		{
			_this->body[i+1]=_this->body[i];
			i--;
		}
		_this->body[i+1]=element;
		_this->length++;
	}
}

Bool List_doesExist(List* _this, int element)
{
	int i=0;
	
	while((_this->length)>i)//원소의 개수만큼 반복
	{
		if((_this->body[i++])==element)//중복이 있을경우
		{
			return T;//TRUE반환
		}
	}

	return F;//중복이 없을경우 FALSE 반환
}
Bool List_isFull(List* _this)
{
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return T;//TRUE 반환
	}

	return F;//현재 FULL이 아닐경우 FALSE 반환
}

Bool List_isIndexOK (List * _this, int index)
{
	if(index>=0&&(_this->length>index))//인덱스값이 0보다 크고 현재 원소수보다 작을경우 
	{
		return T;//TRUE반환
	}

	return F;//아닐경우 FALSE 반환
}
Bool List_isEmpty (List * list)
{
	if(list->length==0)//원소갯수가 0개라면
	{
		return T;//TRUE 반환
	}
	return F;//FALSE 반환
}


void List_reset (List * _this)
{
	_this->length=0;//리스트의 원소수를 0개로 해줌
}


int List_length (List * list)
{
	return list->length;//리스트 길이 반환
}

void List_free (List * list)
{
	free(list->body);//리스트의 배열을 free
}
Element List_deleteKth (List * _this, int K)
{
	int temp=_this->body[K];

	while(K!=_this->length-1)
	{
		_this->body[K]=_this->body[K+1];
		K++;
	}
	_this->length--;

	return temp;
}
Element List_deleteMax (List * _this)
{
	int temp;
	
	temp=_this->body[_this->length-1];
	_this->body[_this->length-1]=0;
	_this->length--;

	return temp;
}
Element List_deleteMin (List * _this)
{
	int temp=_this->body[0];
	int i=0;
	
	while(i!=_this->length-1)
	{
		_this->body[i]=_this->body[i+1];
		i++;
	}
	_this->length--;

	return temp;
}