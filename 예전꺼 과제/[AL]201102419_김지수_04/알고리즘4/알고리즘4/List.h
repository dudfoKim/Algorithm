#pragma once
#include "Global.h"

class List {
	friend class Iter ;
	private:
	int maxLength ; // 배열 body[]의 크기
	int length ; // 리스트에 들어 있는 원소의 개수
	Element * body ; // 실제 리스트의 원소들의 배열
// 모든 원소는 언제나 body[0]부터 차례로 채워져 있게 유지한다.
	public:
	List::List (int MaxSize);
	List::~List ();
	void List::reset ();
	bool List::isFull ();
	bool List::isEmpty ();
	bool List::isIndexOK (int index);
	bool List::doesExist (Element e);
	int List::Length();
	void List::insert (Element e);
	Element List::deleteKth (int K);
	Element List::deleteMin ();
	Element List::deleteMax ();

};