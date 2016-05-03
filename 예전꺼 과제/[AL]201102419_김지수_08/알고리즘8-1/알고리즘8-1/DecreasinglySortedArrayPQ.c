#include <stdlib.h>
#include "DecreasinglySortedArrayPQ.h"

struct _DecreasinglySortedArrayPQ{
	int maxLength;
	int length;
	int* body;
};

DecreasinglySortedArrayPQ * DecreasinglySortedArrayPQ_new (int maxsize)
{
	DecreasinglySortedArrayPQ* temp=NewObject(DecreasinglySortedArrayPQ);//새로운 리스트 동적선언
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

void DecreasinglySortedArrayPQ_free (DecreasinglySortedArrayPQ * _this)
{
	free(_this->body);
}

Bool DecreasinglySortedArrayPQ_isEmpty (DecreasinglySortedArrayPQ * _this)
{
	
	if(_this->length==0)//원소갯수가 0개라면
	{
		return T;//T 반환
	}
	return F;//F 반환
}
Bool DecreasinglySortedArrayPQ_isFull (DecreasinglySortedArrayPQ * _this)
{
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return T;//T 반환
	}

	return F;//현재 FULL이 아닐경우 F 반환
}
void DecreasinglySortedArrayPQ_insert (DecreasinglySortedArrayPQ * _this, Element e)
{
	int i=0, j=0, temp;

	while(i<_this->length)
	{	
		if(e<=_this->body[i])
		{
			i++;
			if(_this->body[i]==-1)
			{
				_this->body[_this->length++]=e;
				i=_this->length;
				break;
			}
		}
		if(e>_this->body[i])
		{
			j=i+1;
			while((_this->length)!=j)
			{
				temp=_this->body[j];
				_this->body[j]=_this->body[j-1];
				j++;
			}
			_this->body[i]=e;
			i=(++_this->length);
		}
	}

	if(_this->length==0)
	{
		_this->body[0]=e;
		_this->length++;
	}
}
Element DecreasinglySortedArrayPQ_deleteMin (DecreasinglySortedArrayPQ * _this)
{
	int min=_this->body[_this->length-1];
	
	_this->body[_this->length-1]=-1;
	_this->length--;	
	return min;
}


