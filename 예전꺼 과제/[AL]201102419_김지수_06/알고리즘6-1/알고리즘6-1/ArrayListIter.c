#include "ArrayListIter.h"



ArrayListIter * ArrayListIter_new (ArrayList * list)
{
	ArrayListIter * _this=NewObject(ArrayListIter);
	_this->list=list;

	return _this;
}

void ArrayListIter_free (ArrayListIter * _this)
{
	free(_this);
	// ��ü�� �Ҹ��Ų��.
	// ���⸦ ä��ÿ�.
}

void ArrayListIter_begin (ArrayListIter * _this)
{
	_this->curLoc=0;
	// �ݺ��ڸ� ����Ʈ�� ó�� ���� ��ġ�� �����Ͽ�, �ݺ��� �����Ѵ�.
	// ���⸦ ä��ÿ�.
}

Bool ArrayListIter_endOfList (ArrayListIter * _this)
{
	if(_this->curLoc==_this->list->length)
	{
		return T;
	}
	return F;
	// ����Ʈ�� �������� �˷��ش�.
	// ���⸦ ä��ÿ�.
}

Element ArrayListIter_currentElement (ArrayListIter * _this)
{
	// ���� ��ġ�� ���Ҹ� ��´�.
	// ���⸦ ä��ÿ�.
	return _this->list->body[_this->curLoc];
}

void ArrayListIter_next (ArrayListIter * _this)
{
	_this->curLoc++;
	// ���� ���� ��ġ�� �ݺ��ڸ� �̵��Ѵ�.
	// ���⸦ ä��ÿ�.
}