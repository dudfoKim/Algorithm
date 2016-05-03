#include <stdlib.h>
#include "SortedArrayList.h"

struct _SortedArrayList{
	int maxLength;
	int length;
	int* body;
};

SortedArrayList * SortedArrayList_new (int maxsize)
{
	SortedArrayList* temp=NewObject(SortedArrayList);//새로운 리스트 동적선언
	int i=0;
	
	temp->maxLength=maxsize;//최대 길이를 최대 사이즈로 
	temp->length=0;//원소초기개수는 0개 
	temp->body=NewVector(int ,maxsize);//배열 동적할당

	while(i<maxsize)
	{
		temp->body[i++]=-1;//배열값 초기화
	}

	return temp;//생성된 리스트 반환
}

void SortedArrayList_free (SortedArrayList * _this)
{
	free(_this->body);
}

Bool SortedArrayList_isEmpty (SortedArrayList * _this)
{
	
	if(_this->length==0)//원소갯수가 0개라면
	{
		return T;//T 반환
	}
	return F;//F 반환
}
Bool SortedArrayList_isFull (SortedArrayList * _this)
{
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return T;//T 반환
	}

	return F;//현재 FULL이 아닐경우 F 반환
}
void SortedArrayList_insert (SortedArrayList * _this, Element e)
{
	int i=0, j=0, temp;
	
	while(i<_this->length)
	{
		if(e>=_this->body[i])
		{
			i++;
			if(_this->body[i]==-1)
			{
				_this->body[_this->length++]=e;
				i=_this->length;
			}
		}
		if(e<=_this->body[i])
		{
			j=i+1;
			while(_this->body[j]!=-1)
			{
				temp=_this->body[j];
				_this->body[j]=_this->body[j-1];
				j++;
			}
			_this->body[i]=e;
			i=++_this->length;
		}
	}
	
}
Element SortedArrayList_min (SortedArrayList * _this)
{
	return _this->body[0];
}
Element SortedArrayList_max (SortedArrayList * _this)
{
	return _this->body[_this->length-1];
}
Bool SortedArrayList_search (SortedArrayList * _this, Element key)
{
	int middle, left=0, right=_this->length-1;
	
	while(left <= right)
	{
		middle = (left + right)/2;

		if(_this->body[middle]<key)
		{
			left=middle;
		}
		else if(_this->body[middle]>key)
		{
			right=middle;
		}
		else
		{
			return T;
		}
	}

	return F;
}


	
	
