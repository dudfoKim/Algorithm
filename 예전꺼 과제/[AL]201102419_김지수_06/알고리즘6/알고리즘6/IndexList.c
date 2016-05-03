#include "IndexList.h"

void IndexList_qsort (IndexList * _this, int left, int right);//index[left] ���� index[right] ������ element���� quick sort �Ѵ�.
void IndexList_swap (IndexList * _this, int i, int j);//index[i]�� index[j]�� ���� �¹ٲ۴�.
int IndexList_compare (IndexList * _this, int i, int j);
//index[i]�� ����Ű�� list�� element�� index[j]�� ����Ű�� list�� element�� ���Ѵ�. �����δ� ���� element ������ ���� item ���� �� ���� return �Ѵ�.
//�Ϲ�������, index[p]�� ����Ű�� list�� element:
//ArrayList_elementAtIndex(indexList->list, indexList->index[p]);

IndexList * IndexList_new ()
{
	// ��ü�� �����Ѵ�.
	IndexList * _this = NewObject(IndexList) ;
	_this->list = NULL ;
	_this->index = NULL ;
	
	return _this ;
}

IndexList * IndexList_newBySortingIndex (ArrayList * list)
{
	// ��ü�� �����Ѵ�.
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
	// ��ü�� �Ҹ��Ų��.
	free(_this->index) ;
	free(_this) ;
}

void IndexList_sortByIndex (IndexList * _this) 
{

	// �־��� ����Ʈ ���ҵ��� ���ĵ� ������ �ε����� �����Ѵ�.
	// ������ quick sort�� ����Ѵ�.
	// �ʱ� �־����� ���Ĺ����� ��� �������̹Ƿ�,
	// index[0] ���� index[ArrayList_length(_this->list)-1] �̴�.
	// ���� �ִ밪�� ��ġ�� ã��, �ε��� ����Ʈ�� �� �������� ���� ���´�.
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
	// index[left] ���� index[right] ������ element���� quick sort �Ѵ�.
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
	// _this->index[i]�� ����Ű�� ����:
	// ArrayList_elementAtIndex(_this->list, _this->index[i])
	// _this->index[j]�� ����Ű�� ����:
	// ArrayList_elementAtIndex(_this->list, _this->index[j])
	// �� �� ���Ҹ� ���Ѵ�.
	// ���⼭��, ���� element ������ ���� element ���� �� ���� return �Ѵ�.
	return ArrayList_elementAtIndex(_this->list, (_this->index[i]))-ArrayList_elementAtIndex(_this->list, (_this->index[j]))  ;
}
