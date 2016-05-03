#include "UnsortedArrayPQ.h"

struct _UnsortedArrayPQ{
	int maxLength;
	int length;
	int* body;
};

UnsortedArrayPQ * UnsortedArrayPQ_new (int maxsize)
{
	int i=0;
	UnsortedArrayPQ* temp=NewObject(UnsortedArrayPQ);//���ο� ����Ʈ ��������

	
	temp->maxLength=maxsize;//�ִ� ���̸� �ִ� ������� 
	temp->length=0;//�����ʱⰳ���� 0�� 
	temp->body=NewVector(int ,maxsize);//�迭 �����Ҵ�

	while(i<maxsize)
	{
		temp->body[i++]=-1;//�迭�� �ʱ�ȭ
	}

	return temp;//������ ����Ʈ ��ȯ

}
void UnsortedArrayPQ_free (UnsortedArrayPQ * _this)
{
	free(_this->body);
}
Bool UnsortedArrayPQ_isEmpty (UnsortedArrayPQ * _this)
{
	if(_this->length==0)//���Ұ����� 0�����
	{
		return T;//T ��ȯ
	}
	return F;//F ��ȯ

}
Bool UnsortedArrayPQ_isFull (UnsortedArrayPQ * _this)
{
	
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return T;//T ��ȯ
	}

	return F;//���� FULL�� �ƴҰ�� F ��ȯ

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