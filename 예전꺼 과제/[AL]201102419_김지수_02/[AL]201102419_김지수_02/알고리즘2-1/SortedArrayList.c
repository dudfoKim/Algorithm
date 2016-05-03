#include <stdlib.h>
#include "SortedArrayList.h"

struct _SortedArrayList{
	int maxLength;
	int length;
	int* body;
};

SortedArrayList * SortedArrayList_new (int maxsize)
{
	SortedArrayList* temp=NewObject(SortedArrayList);//���ο� ����Ʈ ��������
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

void SortedArrayList_free (SortedArrayList * _this)
{
	free(_this->body);
}

Bool SortedArrayList_isEmpty (SortedArrayList * _this)
{
	
	if(_this->length==0)//���Ұ����� 0�����
	{
		return T;//T ��ȯ
	}
	return F;//F ��ȯ
}
Bool SortedArrayList_isFull (SortedArrayList * _this)
{
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return T;//T ��ȯ
	}

	return F;//���� FULL�� �ƴҰ�� F ��ȯ
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


	
	
