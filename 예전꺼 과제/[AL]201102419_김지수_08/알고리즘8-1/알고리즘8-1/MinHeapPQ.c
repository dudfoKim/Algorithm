#include "MinHeapPQ.h"

struct _MinHeapPQ
{
	int size ;
	// number of Elements now in the heap
	int maxSize ;
	// max number of Elements being inserted in the heap tree
	// (maxSize+1) becomes the array size for the heap tree
	int * minHeap ;
};

MinHeapPQ * MinHeapPQ_new (int maxsize)
{
	MinHeapPQ * temp=NewObject(MinHeapPQ);

	temp->maxSize = maxsize ;
	temp->minHeap= NewVector(int, maxsize)  ;
	temp->size = 0 ;

	return temp;
}
void MinHeapPQ_free (MinHeapPQ * _this)
{
// In reverse order of creation
	free(_this->minHeap);
}

Bool MinHeapPQ_isEmpty (MinHeapPQ * _this)
{
	if(_this->size == 0)
	{
		return T;
	}
	return F;
}

Bool MinHeapPQ_isFull (MinHeapPQ * _this)
{
	if(_this->size == _this->maxSize) 
	{
		return T;
	}
	return F;
}

Bool MinHeapPQ_insert (MinHeapPQ * _this, Edge e)
{
	int i ;
	if (_this->size >= _this->maxSize )
	{
		return F; // Heap is full.
	}
	else 
	{
		i = ++(_this->size);
		while ( ( i > 1 ) && (e < _this->minHeap[i/2]) ) 
		{
			_this->minHeap[i] = _this->minHeap[i/2] ;
			i = i / 2 ;
		}
		_this->minHeap[i] = e ;
		return T;
	}
}

Edge MinHeapPQ_deleteMin (MinHeapPQ * _this)
{
	int parent, smallerChild ;
	Edge root, last ;
	// Priority Queue�� empty�� �ƴ϶�� �����Ѵ�. �׷��Ƿ� deleteMin�� call �ϱ� ���� empty �˻縦 �ؾ� �Ѵ�.
	root = _this->minHeap[1] ;
	(_this->size)-- ;
	if ( _this->size > 0 ) 
	{
	// ���� �� �Ŀ� ��� �ϳ��� ���Ұ� ���� �ִ�.
	// ������ ��ġ (size+1)�� ���Ҹ� �����, root ��ġ (1)�κ��� �Ʒ������� ���ο� ��ġ�� ã�� ��������.
		last = _this->minHeap[_this->size+1] ;
		parent = 1 ;
		while ( (parent*2) <= _this->size ) 
		{
	// child �� �����Ѵ�. left, right �߿��� �� ���� cost ���� ���� child�� smallerChild�� �Ѵ�.
		smallerChild = parent * 2 ;
		if ((smallerChild < _this->size)&&(_this->minHeap[smallerChild] > _this->minHeap[smallerChild+1]))
		{
	// right child�� �����ϰ�, �� cost ���� �� �����Ƿ�, right child�� smallerChild�� �Ѵ�.
		smallerChild++ ;
		}
		if ( last <= _this->minHeap[smallerChild] ) 
		{
		break ; // last ���Ҵ� �� �̻� �Ʒ��� ������ �ʿ䰡 ����. ������ parent ��ġ�� �����ϸ� �ȴ�.
		}
	// child ���Ҹ� parent ��ġ�� �÷�������. child ��ġ�� ���ο� parent ��ġ�� �ȴ�.
		_this->minHeap[parent] = _this->minHeap[smallerChild] ;
		parent = smallerChild;
		} // end while
		_this->minHeap[parent] = last ;
	}
	return root ;
}