#include "MinPriorityQ.h"

MinPriorityQ::MinPriorityQ (int maxSize)
{
	this->maxSize = maxSize ;
	this->minHeap= new Element [maxSize+1] ;
	this->size = 0 ;
}
MinPriorityQ::~MinPriorityQ ()
{
// In reverse order of creation
	delete this->minHeap ;
}

bool MinPriorityQ::isEmpty ()
{
	return (this->size == 0) ;
}

bool MinPriorityQ::isFull ()
{
	return (this->size == this->maxSize) ;
}

bool MinPriorityQ::insert (Edge e)
{
	int i ;
	if (this->size >= this->maxSize )
	{
		return false; // Heap is full.
	}
	else 
	{
		i = ++(this->size);
		while ( ( i > 1 ) && (e.cost < this->minHeap[i/2].cost) ) 
		{
			this->minHeap[i] = this->minHeap[i/2] ;
			i = i / 2 ;
		}
		this->minHeap[i] = e ;
		return true;
	}
}

Element MinPriorityQ::deleteMin ()
{
	int parent, smallerChild ;
	Edge root, last ;
	// Priority Queue는 empty가 아니라고 가정한다. 그러므로 deleteMin을 call 하기 전에 empty 검사를 해야 한다.
	root = this->minHeap[1] ;
	(this->size)-- ;
	if ( this->size > 0 ) 
	{
	// 삭제 한 후에 적어도 하나의 원소가 남아 있다.
	// 마지막 위치 (size+1)의 원소를 떼어내어, root 위치 (1)로부터 아래쪽으로 새로운 위치를 찾아 내려간다.
		last = this->minHeap[size+1] ;
		parent = 1 ;
		while ( (parent*2) <= this->size ) 
		{
	// child 가 존재한다. left, right 중에서 더 작은 cost 값을 갖는 child를 smallerChild로 한다.
		smallerChild = parent * 2 ;
		if ((smallerChild < this->size)&&(this->minHeap[smallerChild].cost > this->minHeap[smallerChild+1].cost))
		{
	// right child가 존재하고, 그 cost 값이 더 작으므로, right child를 smallerChild로 한다.
		smallerChild++ ;
		}
		if ( last.cost <= this->minHeap[smallerChild].cost ) 
		{
		break ; // last 원소는 더 이상 아래로 내려갈 필요가 없다. 현재의 parent 위치에 삽입하면 된다.
		}
	// child 원소를 parent 위치로 올려보낸다. child 위치는 새로운 parent 위치가 된다.
		this->minHeap[parent] = this->minHeap[smallerChild] ;
		parent = smallerChild;
		} // end while
		this->minHeap[parent] = last ;
	}
	return root ;
}