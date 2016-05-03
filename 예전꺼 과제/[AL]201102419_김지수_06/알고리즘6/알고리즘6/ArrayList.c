#include "ArrayList.h"

#define List_INIT_LENGTH 10 ;





ArrayList * ArrayList_new ()
{
	ArrayList * _this = NewObject(ArrayList) ;
	_this ->maxLength = List_INIT_LENGTH ;
	_this->body = NewVector(Element, _this->maxLength) ;
	// ����Ʈ�� ���Ҹ� ������ �迭 list->body[]�� ����
	_this->length = 0 ; // ��� ��������Ƿ�, ���� �� ����Ʈ��.
	
	return _this ;
}

void ArrayList_free (ArrayList * _this)
{
	free(_this->body) ; // �迭���� �Ҹ�
	free(_this) ; // �� ����, ��ü �Ҹ�
}

Bool ArrayList_expandLengthInDouble (ArrayList * _this)
{
	int i=0;
	Element * newBody = NewVector(Element, _this->maxLength*2) ;
	// �� �� ������ ���ο� �迭�� ����
	if (newBody == NULL) 
	{
		return F ; // Error in malloc(). �޸� ����
	}
	else 
	{
		while(i<_this->length)
		{
			// ���⸦ ä��ÿ�
			newBody[i]=_this->body[i];
			i++;
		}
		// ���� �迭�� ������ ���ο� �迭�� �����Ͽ� �ű��.
		free(_this->body) ; // ���� �迭�� �Ҹ��Ų��
		_this->body = newBody ;
		_this->maxLength=(_this->maxLength)*2;
		// ���ο� �迭�� list�� �迭�� �����Ѵ�.
		return T ;
	}
}

Bool ArrayList_isFull (ArrayList * _this)
{
	if(_this->length==_this->maxLength)
	{
		return T;
	}
	return F;// ����Ʈ�� Full �̸� TRUE, �ƴϸ� FALSE�� return �Ѵ�.
	// ���⸦ ä��ÿ�.
}

int ArrayList_length(ArrayList * _this)
{
	return _this->length;// ����Ʈ�� length�� return �Ѵ�.
	// ���⸦ ä��ÿ�.
}

Bool ArrayList_add(ArrayList * _this, Element e)
{
	if ( ArrayList_isFull(_this) ) 
	{
// ����Ʈ�� full �̸� FALSE�� return �Ѵ�.
		return F;
	}
	
	else 
	{
		_this->body[_this->length]=e;
		_this->length++;
		// Full�� �ƴϹǷ�, ���� e�� ����Ʈ�� �����Ѵ�.
		// ���⸦ ä��ÿ�.
		return T;
	}
}

Element ArrayList_elementAtIndex(ArrayList * _this, int givenIndex)
{
	// givenIndex�� ����Ʈ�� ���̺��� �۴ٰ� �����Ѵ�.
	// �׷��Ƿ� �� call�� �ϱ� ���� �ݵ�� givenIndex�� ������ �˻��ؾ� �Ѵ�.
	return _this->body[givenIndex] ;
}