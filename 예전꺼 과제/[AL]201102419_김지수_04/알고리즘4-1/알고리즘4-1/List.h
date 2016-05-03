#pragma once
#include "Global.h"

typedef struct _Node Node ;
typedef struct _Node {
	Element item ;
	Node * next ;
}Node ;

class List {
	friend class Iter ;
	private:
	int length ; // 리스트에 들어 있는 원소의 개수
	Node * head ; // 원소들의 연결 리스트의 시작 주소

	public:
	List::List ();
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
	void List::freeLinkedList (Node * node);

};