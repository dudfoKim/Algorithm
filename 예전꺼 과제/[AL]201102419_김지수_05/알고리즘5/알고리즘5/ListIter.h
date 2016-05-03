#pragma once
#include "List.h"
#include "Global.h"

class ListIter 
{
private:
	List * list ;
// �ݺ��� ������ ����Ʈ
	int curLoc ;
// ����Ʈ������ ���� ������ ��ġ
public:
	ListIter::ListIter (List * list);
	ListIter::~ListIter ();
	void ListIter::begin ();
	bool ListIter::endOfList ();
	Element ListIter::currentElement ();
	void ListIter::next ();
	Edge ListIter::getElement();
};