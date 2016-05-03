#pragma once
#include "Global.h"

typedef Edge Element ;
class MinPriorityQ 
{
private:
	int size ;
	// number of Elements now in the heap
	int maxSize ;
	// max number of Elements being inserted in the heap tree
	// (maxSize+1) becomes the array size for the heap tree
	Element * minHeap ;
	// array for a complete binary tree
public:
	MinPriorityQ::MinPriorityQ (int size);
	MinPriorityQ::~MinPriorityQ ();
	bool MinPriorityQ::isEmpty ();
	bool MinPriorityQ::isFull ();
	bool MinPriorityQ::insert (Edge e);
	Edge MinPriorityQ::deleteMin ();
} ;