#include <stdlib.h>
#include "UnsortedArrayList.h"

struct _UnsortedArrayList{
	int maxLength;
	int length;
	int* body;
};



UnsortedArrayList * UnsortedArrayList_new (int maxsize)
{
	UnsortedArrayList* temp=NewObject(UnsortedArrayList);//���ο� ����Ʈ ��������
	int i=0;
	
	temp->maxLength=maxsize;//�ִ� ���̸� �ִ� ������� 
	temp->length=0;//�����ʱⰳ���� 0�� 
	temp->body=NewVector(int ,maxsize);//�迭 �����Ҵ�

	while(i<maxsize)
	{
		temp->body[i++]=0;//�迭�� �ʱ�ȭ
	}

	return temp;//������ ����Ʈ ��ȯ
}

void UnsortedArrayList_free (UnsortedArrayList * _this)
{
	free(_this->body);
}

Bool UnsortedArrayList_isEmpty (UnsortedArrayList * _this)
{
	
	if(_this->length==0)//���Ұ����� 0�����
	{
		return T;//T ��ȯ
	}
	return F;//F ��ȯ
}
Bool UnsortedArrayList_isFull (UnsortedArrayList * _this)
{
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return T;//T ��ȯ
	}

	return F;//���� FULL�� �ƴҰ�� F ��ȯ
}
void UnsortedArrayList_insert (UnsortedArrayList * _this, Element e)
{
	_this->body[_this->length++]=e;//�Է¹����� �־���
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

