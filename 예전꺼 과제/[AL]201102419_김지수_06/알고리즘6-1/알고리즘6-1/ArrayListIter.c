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
	// 객체를 소멸시킨다.
	// 여기를 채우시오.
}

void ArrayListIter_begin (ArrayListIter * _this)
{
	_this->curLoc=0;
	// 반복자를 리스트의 처음 원소 위치로 설정하여, 반복을 시작한다.
	// 여기를 채우시오.
}

Bool ArrayListIter_endOfList (ArrayListIter * _this)
{
	if(_this->curLoc==_this->list->length)
	{
		return T;
	}
	return F;
	// 리스트의 끝인지를 알려준다.
	// 여기를 채우시오.
}

Element ArrayListIter_currentElement (ArrayListIter * _this)
{
	// 현재 위치의 원소를 얻는다.
	// 여기를 채우시오.
	return _this->list->body[_this->curLoc];
}

void ArrayListIter_next (ArrayListIter * _this)
{
	_this->curLoc++;
	// 다음 원소 위치로 반복자를 이동한다.
	// 여기를 채우시오.
}