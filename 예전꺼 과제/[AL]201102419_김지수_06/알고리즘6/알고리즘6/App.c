#include "App.h"

int App_inputNumOfElements (App * _this);
Element App_inputElement (App * _this);
void App_showList (App * _this);
void App_showIndexList (App * _this);
void App_showSortedList (App * _this);

App * App_new()
{
	App * _this = NewObject (App) ;
	_this->list = ArrayList_new () ;
	_this->indexList = NULL ;
	
	return _this ;
}

void App_free(App * _this)
{
	IndexList_free (_this->indexList) ;
	ArrayList_free (_this->list) ;
	free(_this) ;
}

Bool App_inputList (App * _this)
{
	Element e ;
	int count ;
	_this->numOfElements = App_inputNumOfElements(_this) ;
	// ����Ʈ ������ ������ �Է� �޴´�.
	// ������ŭ ���Ҹ� �Է� �޴´�.
	for (count = 0 ; count < _this->numOfElements ; count ++) 
	{
		if ( ArrayList_isFull(_this->list) ) 
		{
			if ( !ArrayList_expandLengthInDouble(_this->list) ) 
			{
				return F; // Error in Size Expansion
			}
		}
		e = App_inputElement(_this) ;
		ArrayList_add(_this->list, e) ;
	}
	
	return T;
}

void App_sortListByIndex (App * _this)
// ����Ʈ �ε����� ����� �ε����� sort �Ѵ�
{
	_this->indexList =IndexList_newBySortingIndex(_this->list) ;
}

void App_showResults (App * _this)
// ����� �����ش�.
{
	App_showList(_this) ;
	App_showIndexList(_this) ;
	App_showSortedList(_this) ;
}

int App_inputNumOfElements (App * _this)
{
	int input;
	printf("[��Ʈ�� �ڷ��� ������ �Է��Ͻÿ�.] : ");
	scanf("%d", &input);
	return input;
}

Element App_inputElement (App * _this)
{
	int input;
	printf("[�迭�� ������ ������ �Է��Ͻÿ�.] : ");
	scanf("%d", &input);


	return input;
	// ���⸦ ä��ÿ�
}

void App_showList (App * _this)
{
	Element e ;
	ArrayListIter * listIter = ArrayListIter_new(_this->list) ;
	ArrayListIter_begin(listIter) ;
	
	printf("[ó���� �־��� ����Ʈ]\n") ;
	
	while ( ! ArrayListIter_endOfList(listIter) ) 
	{
		e = ArrayListIter_currentElement(listIter) ;
		printf("%d ", e) ;
		ArrayListIter_next(listIter) ;
	}
	
	ArrayListIter_free(listIter) ;
}

void App_showIndexList (App * _this)
{
	int index ;
	IndexListIter * indexListIter = IndexListIter_new(_this->indexList) ;
	IndexListIter_begin(indexListIter) ;
	
	printf("\n[���ĵ� �ε��� ����Ʈ]\n") ;
	while ( ! IndexListIter_endOfList(indexListIter) ) 
	{
		index = IndexListIter_currentElement(indexListIter) ;
		printf("%d ", index) ;
		IndexListIter_next(indexListIter) ;
	}
	
	IndexListIter_free(indexListIter) ;
}

void App_showSortedList (App * _this)
{
	int index ;
	Element e ;
	IndexListIter * indexListIter = IndexListIter_new(_this->indexList) ;
	IndexListIter_begin(indexListIter) ;
	
	printf("\n[���ĵ� element ����Ʈ]\n") ;
	
	while ( ! IndexListIter_endOfList(indexListIter) ) 
	{
		index = IndexListIter_currentElement(indexListIter) ;
		e = ArrayList_elementAtIndex(_this->list, index) ;
		printf("%d ", e) ;
		IndexListIter_next(indexListIter) ;
	}
	printf("\n");
	
	IndexListIter_free(indexListIter) ;
}