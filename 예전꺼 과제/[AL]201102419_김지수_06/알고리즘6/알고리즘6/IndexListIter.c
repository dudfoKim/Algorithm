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
	
	// 객체를 소멸시킨다.
	// 여기를 채우시오.
}

void IndexListIter_begin (IndexListIter * _this)
{
	_this->curLoc=0;
	// 반복자를 리스트의 처음 원소 위치로 설정하여, 반복을 시작한다.
	// 여기를 채우시오.
}

Bool IndexListIter_endOfList (IndexListIter * _this)
{
	if(_this->curLoc==_this->indexList->list->length)
	{
		return T;
	}
	return F;
	// 리스트의 끝인지를 알려준다.
	// 여기를 채우시오.
}

Element IndexListIter_currentElement (IndexListIter * _this)
{
	return _this->indexList->index[_this->curLoc];
	// 현재 위치의 원소를 얻는다.
	// 여기를 채우시오.
}

void IndexListIter_next (IndexListIter * _this)
{
	_this->curLoc++;
	// 다음 원소 위치로 반복자를 이동한다.
	// 여기를 채우시오.
}