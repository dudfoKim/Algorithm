#include <stdlib.h>
#include <stdio.h>
#include "List.h"

List::List (int MaxSize)
{//새로운 리스트 동적선언
	int i=0;
	
	this->maxLength=MaxSize;//최대 길이를 최대 사이즈로 
	this->length=0;//원소초기개수는 0개 
	this->body=NewVector(int ,MaxSize);//배열 동적할당

	while(i<MaxSize)
	{
		this->body[i++]=0;//배열값 초기화
	}

	//생성된 리스트 반환
}
List:: ~List ()
{
	free(this->body);
}

void List::insert (Element e)
{
	int i=this->length-1;
	
	if(isFull())
	{
		printf("List FULL!");
	}
	else if(i==-1)
	{
		this->body[i+1]=e;
		this->length++;
	}
	else
	{
		while((i>-1)&&(this->body[i]>=e))
		{
			this->body[i+1]=this->body[i];
			i--;
		}
		this->body[i+1]=e;
		this->length++;
	}
}

bool List::doesExist (Element e)
{
	int i=0;
	
	while((this->length)>i)//원소의 개수만큼 반복
	{
		if((this->body[i++])==e)//중복이 있을경우
		{
			return true;//true반환
		}
	}

	return false;//중복이 없을경우 false 반환
}
bool List::isFull ()
{
	if(this->length==this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return true;//true 반환
	}

	return false;//현재 FULL이 아닐경우 false 반환
}

bool List::isIndexOK (int index)
{
	if(index>=0&&(this->length>index))//인덱스값이 0보다 크고 현재 원소수보다 작을경우 
	{
		return true;//true반환
	}

	return false;//아닐경우 false 반환
}
bool List::isEmpty ()
{
	if(this->length==0)//원소갯수가 0개라면
	{
		return true;//true 반환
	}
	return false;//false 반환
}


void List::reset ()
{
	this->length=0;//리스트의 원소수를 0개로 해줌
}


int List::Length ()
{
	return this->length;//리스트 길이 반환
}


int List::deleteKth (int K)
{
	int temp=this->body[K];

	while(K!=this->length-1)
	{
		this->body[K]=this->body[K+1];
		K++;
	}
	this->length--;

	return temp;
}
Element List::deleteMax ()
{
	int temp;
	
	temp=this->body[this->length-1];
	this->body[this->length-1]=0;
	this->length--;

	return temp;
}
Element List::deleteMin ()
{
	int temp=this->body[0];
	int i=0;
	
	while(i!=this->length-1)
	{
		this->body[i]=this->body[i+1];
		i++;
	}
	this->length--;

	return temp;
}