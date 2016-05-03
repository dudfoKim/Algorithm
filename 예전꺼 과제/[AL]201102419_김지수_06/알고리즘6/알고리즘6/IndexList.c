#include "IndexList.h"

void IndexList_qsort (IndexList * _this, int left, int right);//index[left] 부터 index[right] 까지의 element들을 quick sort 한다.
void IndexList_swap (IndexList * _this, int i, int j);//index[i]와 index[j]의 값을 맞바꾼다.
int IndexList_compare (IndexList * _this, int i, int j);
//index[i]가 가리키는 list의 element와 index[j]가 가리키는 list의 element를 비교한다. 실제로는 앞의 element 값에서 뒤의 item 값을 뺀 값을 return 한다.
//일반적으로, index[p]가 가리키는 list의 element:
//ArrayList_elementAtIndex(indexList->list, indexList->index[p]);

IndexList * IndexList_new ()
{
	// 객체를 생성한다.
	IndexList * _this = NewObject(IndexList) ;
	_this->list = NULL ;
	_this->index = NULL ;
	
	return _this ;
}

IndexList * IndexList_newBySortingIndex (ArrayList * list)
{
	// 객체를 생성한다.
	int i;
	
	IndexList * _this = NewObject (IndexList) ;
	_this->list = list ;
	_this->index = NewVector(Element, ArrayList_length(list)) ;
	for ( i = 0 ; i < ArrayList_length(list) ; i++ ) 
	{
		_this->index[i] = i ;
	}
	IndexList_sortByIndex(_this) ;
	
	return _this ;
}

void IndexList_free (IndexList * _this)
{
	// 객체를 소멸시킨다.
	free(_this->index) ;
	free(_this) ;
}

void IndexList_sortByIndex (IndexList * _this) 
{

	// 주어진 리스트 원소들의 정렬된 순서로 인덱스를 정렬한다.
	// 정렬은 quick sort를 사용한다.
	// 초기 주어지는 정렬범위는 모든 데이터이므로,
	// index[0] 부터 index[ArrayList_length(_this->list)-1] 이다.
	// 먼저 최대값의 위치를 찾아, 인덱스 리스트의 맨 마지막에 갖다 놓는다.
	int maxLocation = 0 ;
	int current;
	int listLength = ArrayList_length(_this->list) ;
	
	for (current = 1 ; current < listLength ; current ++) 
	{
		if (IndexList_compare(_this, current, maxLocation) > 0)
			maxLocation = current ;
	}
	IndexList_swap (_this, maxLocation, listLength-1) ;
	IndexList_qsort(_this, 0, listLength-2) ;
}

void IndexList_qsort (IndexList * _this, int left, int right)
{
	// index[left] 부터 index[right] 까지의 element들을 quick sort 한다.
	int up, down, pivotLoc ;
	if ( left < right ) 
	{
		pivotLoc = left ;
		up = left ;
		down = right + 1 ;
		do 
		{
			do 
			{ 
				up++; 
			}while (IndexList_compare(_this, up, pivotLoc) < 0) ;
			do 
			{ 
				down--; 
			}while (IndexList_compare(_this, down, pivotLoc) > 0) ;
			if ( up < down )
				IndexList_swap(_this, up, down) ;
		} while ( up < down ) ;
			
		IndexList_swap(_this, pivotLoc, down) ;
		IndexList_qsort(_this, left, down-1) ;
		IndexList_qsort(_this, down+1, right) ;
	}
}

void IndexList_swap (IndexList * _this, int i, int j)
{
	int temp;
	temp=_this->index[i];
	_this->index[i]=_this->index[j];
	_this->index[j]=temp;
	
}

int IndexList_compare (IndexList * _this, int i, int j)
{
	// _this->index[i]가 가리키는 원소:
	// ArrayList_elementAtIndex(_this->list, _this->index[i])
	// _this->index[j]가 가리키는 원소:
	// ArrayList_elementAtIndex(_this->list, _this->index[j])
	// 이 두 원소를 비교한다.
	// 여기서는, 앞의 element 값에서 뒤의 element 값을 뺀 값을 return 한다.
	return ArrayList_elementAtIndex(_this->list, (_this->index[i]))-ArrayList_elementAtIndex(_this->list, (_this->index[j]))  ;
}
