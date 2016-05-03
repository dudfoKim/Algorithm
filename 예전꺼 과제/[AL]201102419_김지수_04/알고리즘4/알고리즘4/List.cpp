#include <stdlib.h>
#include <stdio.h>
#include "List.h"

List::List (int MaxSize)
{//���ο� ����Ʈ ��������
	int i=0;
	
	this->maxLength=MaxSize;//�ִ� ���̸� �ִ� ������� 
	this->length=0;//�����ʱⰳ���� 0�� 
	this->body=NewVector(int ,MaxSize);//�迭 �����Ҵ�

	while(i<MaxSize)
	{
		this->body[i++]=0;//�迭�� �ʱ�ȭ
	}

	//������ ����Ʈ ��ȯ
}
List:: ~List ()
{
	free(this->body);
}

void List::insert (Element e)
{
	int i=this->length-1;
	
	if(isFull())
	{
		printf("List FULL!");
	}
	else if(i==-1)
	{
		this->body[i+1]=e;
		this->length++;
	}
	else
	{
		while((i>-1)&&(this->body[i]>=e))
		{
			this->body[i+1]=this->body[i];
			i--;
		}
		this->body[i+1]=e;
		this->length++;
	}
}

bool List::doesExist (Element e)
{
	int i=0;
	
	while((this->length)>i)//������ ������ŭ �ݺ�
	{
		if((this->body[i++])==e)//�ߺ��� �������
		{
			return true;//true��ȯ
		}
	}

	return false;//�ߺ��� ������� false ��ȯ
}
bool List::isFull ()
{
	if(this->length==this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return true;//true ��ȯ
	}

	return false;//���� FULL�� �ƴҰ�� false ��ȯ
}

bool List::isIndexOK (int index)
{
	if(index>=0&&(this->length>index))//�ε������� 0���� ũ�� ���� ���Ҽ����� ������� 
	{
		return true;//true��ȯ
	}

	return false;//�ƴҰ�� false ��ȯ
}
bool List::isEmpty ()
{
	if(this->length==0)//���Ұ����� 0�����
	{
		return true;//true ��ȯ
	}
	return false;//false ��ȯ
}


void List::reset ()
{
	this->length=0;//����Ʈ�� ���Ҽ��� 0���� ����
}


int List::Length ()
{
	return this->length;//����Ʈ ���� ��ȯ
}


int List::deleteKth (int K)
{
	int temp=this->body[K];

	while(K!=this->length-1)
	{
		this->body[K]=this->body[K+1];
		K++;
	}
	this->length--;

	return temp;
}
Element List::deleteMax ()
{
	int temp;
	
	temp=this->body[this->length-1];
	this->body[this->length-1]=0;
	this->length--;

	return temp;
}
Element List::deleteMin ()
{
	int temp=this->body[0];
	int i=0;
	
	while(i!=this->length-1)
	{
		this->body[i]=this->body[i+1];
		i++;
	}
	this->length--;

	return temp;
}