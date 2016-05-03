#include <stdlib.h>
#include "UnsortedArrayList.h"

struct _UnsortedArrayList{
	int maxLength;
	int length;
	int* body;
};



UnsortedArrayList * UnsortedArrayList_new (int maxsize)
{
	UnsortedArrayList* temp=NewObject(UnsortedArrayList);//새로운 리스트 동적선언
	int i=0;
	
	temp->maxLength=maxsize;//최대 길이를 최대 사이즈로 
	temp->length=0;//원소초기개수는 0개 
	temp->body=NewVector(int ,maxsize);//배열 동적할당

	while(i<maxsize)
	{
		temp->body[i++]=0;//배열값 초기화
	}

	return temp;//생성된 리스트 반환
}

void UnsortedArrayList_free (UnsortedArrayList * _this)
{
	free(_this->body);
}

Bool UnsortedArrayList_isEmpty (UnsortedArrayList * _this)
{
	
	if(_this->length==0)//원소갯수가 0개라면
	{
		return T;//T 반환
	}
	return F;//F 반환
}
Bool UnsortedArrayList_isFull (UnsortedArrayList * _this)
{
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return T;//T 반환
	}

	return F;//현재 FULL이 아닐경우 F 반환
}
void UnsortedArrayList_insert (UnsortedArrayList * _this, Element e)
{
	_this->body[_this->length++]=e;//입력받은값 넣어줌
}
Element UnsortedArrayList_min (UnsortedArrayList * _this)
{
	int i=1, min=_this->body[0];
	
	while(i<_this->maxLength)
	{
		if(_this->body[i]<min)
		{
			min=_this->body[i];
		}
		i++;
	}

	return min;
}
Element UnsortedArrayList_max (UnsortedArrayList * _this)
{
	int i=1, max=_this->body[0];
	
	while(i<_this->maxLength)
	{
		if(_this->body[i]>max)
		{
			max=_this->body[i];
		}
		i++;
	}

	return max;
}
Bool UnsortedArrayList_search (UnsortedArrayList * _this, Element key)
{
	int i=0;
	
	while(i<_this->maxLength)
	{
		if(_this->body[i]==key)
		{
			return T;
		}
		i++;
	}
	return F;
}

