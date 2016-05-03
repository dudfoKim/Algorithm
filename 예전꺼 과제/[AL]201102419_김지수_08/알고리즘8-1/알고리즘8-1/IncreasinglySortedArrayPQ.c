#include <stdlib.h>
#include "IncreasinglySortedArrayPQ.h"

struct _IncreasinglySortedArrayPQ{
	int maxLength;
	int length;
	int* body;
};

IncreasinglySortedArrayPQ * IncreasinglySortedArrayPQ_new (int maxsize)
{
	IncreasinglySortedArrayPQ* temp=NewObject(IncreasinglySortedArrayPQ);//���ο� ����Ʈ ��������
	int i=0;
	
	temp->maxLength=maxsize;//�ִ� ���̸� �ִ� ������� 
	temp->length=0;//�����ʱⰳ���� 0�� 
	temp->body=NewVector(int ,maxsize);//�迭 �����Ҵ�

	while(i<maxsize)
	{
		temp->body[i++]=-1;//�迭�� �ʱ�ȭ
	}

	return temp;//������ ����Ʈ ��ȯ
}

void IncreasinglySortedArrayPQ_free (IncreasinglySortedArrayPQ * _this)
{
	free(_this->body);
}

Bool IncreasinglySortedArrayPQ_isEmpty (IncreasinglySortedArrayPQ * _this)
{
	
	if(_this->length==0)//���Ұ����� 0�����
	{
		return T;//T ��ȯ
	}
	return F;//F ��ȯ
}
Bool IncreasinglySortedArrayPQ_isFull (IncreasinglySortedArrayPQ * _this)
{
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return T;//T ��ȯ
	}

	return F;//���� FULL�� �ƴҰ�� F ��ȯ
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

