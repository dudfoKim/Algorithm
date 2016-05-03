#include "UnsortedArrayPQ.h"

struct _UnsortedArrayPQ{
	int maxLength;
	int length;
	int* body;
};

UnsortedArrayPQ * UnsortedArrayPQ_new (int maxsize)
{
	int i=0;
	UnsortedArrayPQ* temp=NewObject(UnsortedArrayPQ);//새로운 리스트 동적선언

	
	temp->maxLength=maxsize;//최대 길이를 최대 사이즈로 
	temp->length=0;//원소초기개수는 0개 
	temp->body=NewVector(int ,maxsize);//배열 동적할당

	while(i<maxsize)
	{
		temp->body[i++]=-1;//배열값 초기화
	}

	return temp;//생성된 리스트 반환

}
void UnsortedArrayPQ_free (UnsortedArrayPQ * _this)
{
	free(_this->body);
}
Bool UnsortedArrayPQ_isEmpty (UnsortedArrayPQ * _this)
{
	if(_this->length==0)//원소갯수가 0개라면
	{
		return T;//T 반환
	}
	return F;//F 반환

}
Bool UnsortedArrayPQ_isFull (UnsortedArrayPQ * _this)
{
	
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return T;//T 반환
	}

	return F;//현재 FULL이 아닐경우 F 반환

}
void UnsortedArrayPQ_insert (UnsortedArrayPQ * _this, Element e)
{
	int i=0, j=0, temp;
	
	_this->body[_this->length]=e;

	_this->length++;

}
Element UnsortedArrayPQ_deleteMin (UnsortedArrayPQ * _this)
{
	int i=0,temp;

	temp=0;

	while(i<_this->length)
	{
		if(_this->body[i]>_this->body[temp])
		{
			temp=i;
		}
		
		i++;
	}
	i=temp;
	
	while(temp!=_this->length)
	{
		_this->body[temp]=_this->body[++temp];
	}
	return i;
}