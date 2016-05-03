#include <stdlib.h>
#include "DecreasinglySortedArrayPQ.h"

struct _DecreasinglySortedArrayPQ{
	int maxLength;
	int length;
	int* body;
};

DecreasinglySortedArrayPQ * DecreasinglySortedArrayPQ_new (int maxsize)
{
	DecreasinglySortedArrayPQ* temp=NewObject(DecreasinglySortedArrayPQ);//���ο� ����Ʈ ��������
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

void DecreasinglySortedArrayPQ_free (DecreasinglySortedArrayPQ * _this)
{
	free(_this->body);
}

Bool DecreasinglySortedArrayPQ_isEmpty (DecreasinglySortedArrayPQ * _this)
{
	
	if(_this->length==0)//���Ұ����� 0�����
	{
		return T;//T ��ȯ
	}
	return F;//F ��ȯ
}
Bool DecreasinglySortedArrayPQ_isFull (DecreasinglySortedArrayPQ * _this)
{
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return T;//T ��ȯ
	}

	return F;//���� FULL�� �ƴҰ�� F ��ȯ
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


