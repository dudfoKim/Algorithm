#pragma once
#include "Global.h"
#include "List.h"

class Iter
{
	private:
	List * list ; // 검색해야 할 리스트
	int currentLocation ; //현재 (노드) 위치
	public:
	Iter::Iter (List * list);
	Iter::~Iter ();
	void Iter::begin ();
	bool Iter::endOfList ();
	int Iter::currentElement ();
	void Iter::next ();

} ;