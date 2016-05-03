#include "IndexListIter.h"



IndexListIter * IndexListIter_new (IndexList * list)
{
	IndexListIter * _this=NewObject(IndexListIter);
	_this->indexList=list;

	return _this;
}

void IndexListIter_free (IndexListIter * _this)
{
	free(_this);
	
	// ��ü�� �Ҹ��Ų��.
	// ���⸦ ä��ÿ�.
}

void IndexListIter_begin (IndexListIter * _this)
{
	_this->curLoc=0;
	// �ݺ��ڸ� ����Ʈ�� ó�� ���� ��ġ�� �����Ͽ�, �ݺ��� �����Ѵ�.
	// ���⸦ ä��ÿ�.
}

Bool IndexListIter_endOfList (IndexListIter * _this)
{
	if(_this->curLoc==_this->indexList->list->length)
	{
		return T;
	}
	return F;
	// ����Ʈ�� �������� �˷��ش�.
	// ���⸦ ä��ÿ�.
}

Element IndexListIter_currentElement (IndexListIter * _this)
{
	return _this->indexList->index[_this->curLoc];
	// ���� ��ġ�� ���Ҹ� ��´�.
	// ���⸦ ä��ÿ�.
}

void IndexListIter_next (IndexListIter * _this)
{
	_this->curLoc++;
	// ���� ���� ��ġ�� �ݺ��ڸ� �̵��Ѵ�.
	// ���⸦ ä��ÿ�.
}