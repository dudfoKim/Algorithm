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
	// Priority Queue는 empty가 아니라고 가정한다. 그러므로 deleteMin을 call 하기 전에 empty 검사를 해야 한다.
	root = _this->minHeap[1] ;
	(_this->size)-- ;
	if ( _this->size > 0 ) 
	{
	// 삭제 한 후에 적어도 하나의 원소가 남아 있다.
	// 마지막 위치 (size+1)의 원소를 떼어내어, root 위치 (1)로부터 아래쪽으로 새로운 위치를 찾아 내려간다.
		last = _this->minHeap[_this->size+1] ;
		parent = 1 ;
		while ( (parent*2) <= _this->size ) 
		{
	// child 가 존재한다. left, right 중에서 더 작은 cost 값을 갖는 child를 smallerChild로 한다.
		smallerChild = parent * 2 ;
		if ((smallerChild < _this->size)&&(_this->minHeap[smallerChild] > _this->minHeap[smallerChild+1]))
		{
	// right child가 존재하고, 그 cost 값이 더 작으므로, right child를 smallerChild로 한다.
		smallerChild++ ;
		}
		if ( last <= _this->minHeap[smallerChild] ) 
		{
		break ; // last 원소는 더 이상 아래로 내려갈 필요가 없다. 현재의 parent 위치에 삽입하면 된다.
		}
	// child 원소를 parent 위치로 올려보낸다. child 위치는 새로운 parent 위치가 된다.
		_this->minHeap[parent] = _this->minHeap[smallerChild] ;
		parent = smallerChild;
		} // end while
		_this->minHeap[parent] = last ;
	}
	return root ;
}