#pragma once
#include "Global.h"

typedef Edge Element ;
class List 
{
private:
	friend class ListIter ;
	int maxSize;
	// max number of Elements being inserted in the list
	int size;
	// number of Elements now in the list
	Element * body ;
	// array for the list
public:
	List::List (int size);
	List::~List ();
	bool List::isEmpty ();
	bool List::isFull ();
	bool List::insert (Element e);
	int List::getsize();//return size
};