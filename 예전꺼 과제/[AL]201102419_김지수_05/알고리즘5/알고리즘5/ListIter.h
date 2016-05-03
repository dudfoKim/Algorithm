#pragma once
#include "List.h"
#include "Global.h"

class ListIter 
{
private:
	List * list ;
// 반복을 실행할 리스트
	int curLoc ;
// 리스트에서의 현재 원소의 위치
public:
	ListIter::ListIter (List * list);
	ListIter::~ListIter ();
	void ListIter::begin ();
	bool ListIter::endOfList ();
	Element ListIter::currentElement ();
	void ListIter::next ();
	Edge ListIter::getElement();
};