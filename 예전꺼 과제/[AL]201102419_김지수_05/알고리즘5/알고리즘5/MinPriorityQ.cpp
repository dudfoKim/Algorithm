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
	// Priority Queue�� empty�� �ƴ϶�� �����Ѵ�. �׷��Ƿ� deleteMin�� call �ϱ� ���� empty �˻縦 �ؾ� �Ѵ�.
	root = this->minHeap[1] ;
	(this->size)-- ;
	if ( this->size > 0 ) 
	{
	// ���� �� �Ŀ� ��� �ϳ��� ���Ұ� ���� �ִ�.
	// ������ ��ġ (size+1)�� ���Ҹ� �����, root ��ġ (1)�κ��� �Ʒ������� ���ο� ��ġ�� ã�� ��������.
		last = this->minHeap[size+1] ;
		parent = 1 ;
		while ( (parent*2) <= this->size ) 
		{
	// child �� �����Ѵ�. left, right �߿��� �� ���� cost ���� ���� child�� smallerChild�� �Ѵ�.
		smallerChild = parent * 2 ;
		if ((smallerChild < this->size)&&(this->minHeap[smallerChild].cost > this->minHeap[smallerChild+1].cost))
		{
	// right child�� �����ϰ�, �� cost ���� �� �����Ƿ�, right child�� smallerChild�� �Ѵ�.
		smallerChild++ ;
		}
		if ( last.cost <= this->minHeap[smallerChild].cost ) 
		{
		break ; // last ���Ҵ� �� �̻� �Ʒ��� ������ �ʿ䰡 ����. ������ parent ��ġ�� �����ϸ� �ȴ�.
		}
	// child ���Ҹ� parent ��ġ�� �÷�������. child ��ġ�� ���ο� parent ��ġ�� �ȴ�.
		this->minHeap[parent] = this->minHeap[smallerChild] ;
		parent = smallerChild;
		} // end while
		this->minHeap[parent] = last ;
	}
	return root ;
}