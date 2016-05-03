#include <stdlib.h>
#include <stdio.h>
#include "List.h"

List* List_new(int maxSize)
{
	List* temp=NewObject(List);//���ο� ����Ʈ ��������
	int i=0;
	
	temp->maxLength=maxSize;//�ִ� ���̸� �ִ� ������� 
	temp->length=0;//�����ʱⰳ���� 0�� 
	temp->body=NewVector(int ,maxSize);//�迭 �����Ҵ�

	while(i<maxSize)
	{
		temp->body[i++]=0;//�迭�� �ʱ�ȭ
	}

	return temp;//������ ����Ʈ ��ȯ
}

void List_insert(List* _this, int element)
{
	int i=_this->length-1;
	
	if(List_isFull(_this))
	{
		printf("List FULL!");
	}
	else if(i==-1)
	{
		_this->body[i+1]=element;
		_this->length++;
	}
	else
	{
		while((i>-1)&&(_this->body[i]>=element))
		{
			_this->body[i+1]=_this->body[i];
			i--;
		}
		_this->body[i+1]=element;
		_this->length++;
	}
}

Bool List_doesExist(List* _this, int element)
{
	int i=0;
	
	while((_this->length)>i)//������ ������ŭ �ݺ�
	{
		if((_this->body[i++])==element)//�ߺ��� �������
		{
			return T;//TRUE��ȯ
		}
	}

	return F;//�ߺ��� ������� FALSE ��ȯ
}
Bool List_isFull(List* _this)
{
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return T;//TRUE ��ȯ
	}

	return F;//���� FULL�� �ƴҰ�� FALSE ��ȯ
}

Bool List_isIndexOK (List * _this, int index)
{
	if(index>=0&&(_this->length>index))//�ε������� 0���� ũ�� ���� ���Ҽ����� ������� 
	{
		return T;//TRUE��ȯ
	}

	return F;//�ƴҰ�� FALSE ��ȯ
}
Bool List_isEmpty (List * list)
{
	if(list->length==0)//���Ұ����� 0�����
	{
		return T;//TRUE ��ȯ
	}
	return F;//FALSE ��ȯ
}


void List_reset (List * _this)
{
	_this->length=0;//����Ʈ�� ���Ҽ��� 0���� ����
}


int List_length (List * list)
{
	return list->length;//����Ʈ ���� ��ȯ
}

void List_free (List * list)
{
	free(list->body);//����Ʈ�� �迭�� free
}
Element List_deleteKth (List * _this, int K)
{
	int temp=_this->body[K];

	while(K!=_this->length-1)
	{
		_this->body[K]=_this->body[K+1];
		K++;
	}
	_this->length--;

	return temp;
}
Element List_deleteMax (List * _this)
{
	int temp;
	
	temp=_this->body[_this->length-1];
	_this->body[_this->length-1]=0;
	_this->length--;

	return temp;
}
Element List_deleteMin (List * _this)
{
	int temp=_this->body[0];
	int i=0;
	
	while(i!=_this->length-1)
	{
		_this->body[i]=_this->body[i+1];
		i++;
	}
	_this->length--;

	return temp;
}