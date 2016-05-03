#include <stdlib.h>
#include "IncreasinglySortedArrayPQ.h"

struct _IncreasinglySortedArrayPQ{
	int maxLength;
	int length;
	int* body;
};

IncreasinglySortedArrayPQ * IncreasinglySortedArrayPQ_new (int maxsize)
{
	IncreasinglySortedArrayPQ* temp=NewObject(IncreasinglySortedArrayPQ);//새로운 리스트 동적선언
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

void IncreasinglySortedArrayPQ_free (IncreasinglySortedArrayPQ * _this)
{
	free(_this->body);
}

Bool IncreasinglySortedArrayPQ_isEmpty (IncreasinglySortedArrayPQ * _this)
{
	
	if(_this->length==0)//원소갯수가 0개라면
	{
		return T;//T 반환
	}
	return F;//F 반환
}
Bool IncreasinglySortedArrayPQ_isFull (IncreasinglySortedArrayPQ * _this)
{
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return T;//T 반환
	}

	return F;//현재 FULL이 아닐경우 F 반환
}
void IncreasinglySortedArrayPQ_insert (IncreasinglySortedArrayPQ * _this, Element e)
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
				break;
			}
		}
		if(e<_this->body[i])
		{
			j=i+1;
			while((_this->length)!=j)
			{
				temp=_this->body[j];
				_this->body[j]=_this->body[j-1];
				j++;
			}
			_this->body[i]=e;
			i=++_this->length;
		}
	}

	if(_this->length==0)
	{
		_this->body[0]=e;
		_this->length++;
	}
}
Element IncreasinglySortedArrayPQ_deleteMin (IncreasinglySortedArrayPQ * _this)
{
	int i=0, min;
	
	min=_this->body[i];

	while(i<_this->length)
	{
		_this->body[i]=_this->body[i+1];
		i++;
	}
	_this->length--;

	return min;
}

