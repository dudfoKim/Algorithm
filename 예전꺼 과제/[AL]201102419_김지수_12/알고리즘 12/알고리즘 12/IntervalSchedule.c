#include "IntervalSchedule.h"

void IntervalSchedule_sortIntervalIndex(IntervalSchedule * _this);
void IntervalSchedule_qsort(IntervalSchedule * _this, int left, int right);
int IntervalSchedule_compare (IntervalSchedule * _this, int i, int j);
void IntervalSchedule_swap (IntervalSchedule * _this, int i, int j) ;

IntervalSchedule * IntervalSchedule_new()
{
	IntervalSchedule * temp = NewObject(IntervalSchedule);

	return temp;
}
void IntervalSchedule_free (IntervalSchedule * _this)
{
	free(_this);
}
Bool IntervalSchedule_inputIntervals (IntervalSchedule * _this)
{
	int i=0;

	printf("Interval의 갯수를 입력하세요 : ");
	scanf("%d", &_this->numOfIntervals);

	while(i<_this->numOfIntervals)
	{
		while(1)
		{
			printf("%d번째 Interval을 입력하세요 : [start] [finish]", i);
			scanf("%d %d", &_this->interval[i].start, &_this->interval[i].finish);
			if(_this->interval[i].start < _this->interval[i].finish)
			{
				break;
			}
		}
		i++;
	}
//Interval의 개수를 입력 받는다.
//개수만큼 interval을 반복하여 입력 받는다.
//start < finish 가 성립하지 않으면 다시 입력 받는다.
}
void IntervalSchedule_runGreedy (IntervalSchedule * _this)
{
	Time lastFinish = 0 ;
	int currentIndex ;
	int i;

	_this->optimalSet = IntervalList_new() ;
	IntervalSchedule_sortIntervalIndex(_this) ;
	for ( i=0 ; i <_this->numOfIntervals ; i++) 
	{
		currentIndex = _this->sortedIndex[i] ;
		if (_this->interval[currentIndex].start >= lastFinish) 
		{
			IntervalList_add(_this->optimalSet, currentIndex) ;
			lastFinish = _this->interval[currentIndex].finish ;
		}
	}
//Interval을, finish의 증가 순서로 quick sort 한다.
//greedy algorithm을 적용하여 optimal set을 찾는다.
}
void IntervalSchedule_showResults (IntervalSchedule * _this)
{
	int i=0;
	ListIterator * iter;

	iter = ListIterator_new(_this->optimalSet);

	printf("입력된 순서의 스케쥴\n");
	while (i<_this->numOfIntervals ) 
	{
		printf("[%d, %d] ", _this->interval[i].start, _this->interval[i].finish);
		i++;
	}
	
	i=0;

	printf("\nfinish로 정렬된 순서의 스케쥴\n");
	while(i<_this->numOfIntervals)
	{
		printf("[%d, %d] ", _this->interval[_this->sortedIndex[i]].start, _this->interval[_this->sortedIndex[i]].finish);
		i++;
	}
	
	ListIterator_begin(iter);
	
	printf("\noptimalSet\n");
	while ( ! ListIterator_end(iter) ) 
	{
		i = ListIterator_currentElement(iter) ;
		printf("[%d, %d]\n", _this->interval[i].start, _this->interval[i].finish);
		ListIterator_next(iter) ;
	}
	
	ListIterator_free(iter) ;


//interval[]을 입력된 순서대로 출력한다.
//sortedIndex[]를 이용하여 interval[]을 finish로 sort 된 순서로 출력한다.
//optimalSet의 내용을 출력한다.
}

void IntervalSchedule_sortIntervalIndex(IntervalSchedule * _this)
{
	int i=0;
	int maxLocation=0;
	
//sortedIndex[]를 생성한다.
//각 sortedIndex[i]가 interval[i]를 가리키도록 sortedIndex[]를 초기화 한다.
	for (i=0 ; i<_this->numOfIntervals; i++) 
	{
		_this->sortedIndex[i] = i ;
		
	}

	for (i = 1 ; i < _this->numOfIntervals ; i ++) 
	{
		if (IntervalSchedule_compare(_this, i, maxLocation) > 0)
			maxLocation = i ;
	}
	IntervalSchedule_swap (_this, maxLocation, _this->numOfIntervals-1) ;
	
	IntervalSchedule_qsort(_this, 0, _this->numOfIntervals-2) ;
	
	
//sortedIndex를 interval[]의 finish의 크기 순서로 quick sort한다.
//quick sort 자체는 다음의 recursive function을 call 한다.
		
}
int IntervalSchedule_compare (IntervalSchedule * _this, int i, int j)
{
	return (_this->interval[_this->sortedIndex[i]].finish - _this->interval[_this->sortedIndex[j]].finish) ;
}
void IntervalSchedule_qsort( IntervalSchedule * _this, int left, int right)
{
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
			}while (IntervalSchedule_compare(_this, up, pivotLoc) <= 0) ;
			do 
			{ 
				down--; 
			}while (IntervalSchedule_compare(_this, down, pivotLoc) > 0) ;
			if ( up < down )
				IntervalSchedule_swap(_this, up, down) ;
		} while ( up < down ) ;
			
		IntervalSchedule_swap(_this, pivotLoc, down) ;
		IntervalSchedule_qsort(_this, left, down-1) ;
		IntervalSchedule_qsort(_this, down+1, right) ;
	}
 
}

void IntervalSchedule_swap (IntervalSchedule * _this, int i, int j)
{
	int temp=_this->sortedIndex[i];
	_this->sortedIndex[i]=_this->sortedIndex[j];
	_this->sortedIndex[j]=temp;
}










