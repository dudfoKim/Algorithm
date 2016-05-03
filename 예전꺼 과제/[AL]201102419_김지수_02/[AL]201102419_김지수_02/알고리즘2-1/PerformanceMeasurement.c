#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PerformanceMeasurement.h"


#define MaxTestSize 10000
#define NumOfTests 5
#define FirstTestSize 1000 // 첫번째 실험 데이터 크기
#define SizeIncrement 1000 // 실험 데이터 크기 증가량

struct _PerformanceMeasurement{
	int maxTestSize ;
	int * data ; // array for test data
	int numOfTests ;
	int * testSizes ; //매번 테스트 해야 할 데이터 크기가 저장되는 배열
	Timer * timer ;
};

void PerformanceMeasurement_generateData(PerformanceMeasurement* _this)
{
	int i = 0 ;
	srand((unsigned) time(NULL));

	while ( i< _this->maxTestSize ) 
	{
		_this->data[i] = rand() % _this->maxTestSize ;
		i++ ;
	}
}


PerformanceMeasurement * PerformanceMeasurement_New()
{
	int i ;
	PerformanceMeasurement * _this = NewObject(PerformanceMeasurement);// 객체 생성
	_this->maxTestSize = MaxTestSize ; // 데이터 최대 크기 설정
	_this->numOfTests = NumOfTests ; // 각 구현에 대한 실험 회수
	_this->data = NewVector(Element,MaxTestSize) ; // 실험 데이터 저장 배열
	_this->testSizes = NewVector(int,NumOfTests) ; //실험별 데이터 크기 저장 배열
	i = 0 ;

	while (i < NumOfTests) 
	{ // 실험별 데이터 크기 설정
		_this->testSizes[i] = FirstTestSize + SizeIncrement * i ;
		i++;
	}
	
	_this->timer = Timer_new() ;

	return _this;
}

void PerformanceMeasurement_testUnsortedArray (PerformanceMeasurement * _this)
{
	UnsortedArrayList * list ;
	Element min, max ;
	int i, testCount, testSize ;
	Bool found ;
	double insertTime, minTime, maxTime, searchTime ;
	printf("\n[Unsorted Array]") ;
	for ( testCount = 0 ; testCount < _this->numOfTests ; testCount++ ) 
	{
		testSize = _this->testSizes[testCount] ;
		list = UnsortedArrayList_new (testSize) ;
		insertTime = minTime = maxTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;
			UnsortedArrayList_insert (list, _this->data[i]) ;
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			min = UnsortedArrayList_min (list) ;
			Timer_stop (_this->timer) ;
			minTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			max = UnsortedArrayList_max (list) ;
			Timer_stop (_this->timer) ;
			maxTime += Timer_duration (_this->timer) ;
		}
		searchTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++) 
		{
			Timer_start (_this->timer) ;
			found = UnsortedArrayList_search (list, _this->data[i]) ;
			Timer_stop (_this->timer) ;
			searchTime += Timer_duration (_this->timer) ;
		}
		
		printf("\n크기: %d, 삽입하기: %d, 최소값찾기: %d , 최대값찾기: %d , 검색하기: %d", testSize, (long)insertTime, (long)minTime, (long)maxTime, (long)searchTime);
		UnsortedArrayList_free (list) ;
	}
}

void PerformanceMeasurement_testSortedArray (PerformanceMeasurement * _this)
{
	SortedArrayList * list ;
	Element min, max ;
	int i, testCount, testSize ;
	Bool found ;
	double insertTime, minTime, maxTime, searchTime ;
	printf("\n[Sorted Array]") ;
	for ( testCount = 0 ; testCount < _this->numOfTests ; testCount++ ) 
	{
		testSize = _this->testSizes[testCount] ;
		list = SortedArrayList_new (testSize) ;
		insertTime = minTime = maxTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;
			SortedArrayList_insert (list, _this->data[i]) ;
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			min = SortedArrayList_min (list) ;
			Timer_stop (_this->timer) ;
			minTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			max = SortedArrayList_max (list) ;
			Timer_stop (_this->timer) ;
			maxTime += Timer_duration (_this->timer) ;
		}
		searchTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++) 
		{
			Timer_start (_this->timer) ;
			found = SortedArrayList_search (list, _this->data[i]) ;
			Timer_stop (_this->timer) ;
			searchTime += Timer_duration (_this->timer) ;
		}
		
		printf("\n크기: %d, 삽입하기: %d, 최소값찾기: %d , 최대값찾기: %d , 검색하기: %d", testSize, (long)insertTime, (long)minTime, (long)maxTime, (long)searchTime);
		SortedArrayList_free (list) ;
	}
}

void  PerformanceMeasurement_testUnsortedLinkedList (PerformanceMeasurement * _this) 
{
	UnsortedLinkedList * list ;
	Element min, max ;
	int i, testCount, testSize ;
	Bool found ;
	double insertTime, minTime, maxTime, searchTime ;
	printf("\n[UnsortedLinkedList]") ;
	for ( testCount = 0 ; testCount < _this->numOfTests ; testCount++ ) 
	{
		testSize = _this->testSizes[testCount] ;
		list = UnsortedLinkedList_new() ;
		insertTime = minTime = maxTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;
			
			UnsortedLinkedList_insert (list, _this->data[i]) ;
					
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			min = UnsortedLinkedList_min (list) ;
				
			Timer_stop (_this->timer) ;
			minTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			max = UnsortedLinkedList_max (list) ;
			Timer_stop (_this->timer) ;
			maxTime += Timer_duration (_this->timer) ;
		
		}
		searchTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++) 
		{
			Timer_start (_this->timer) ;
			found = UnsortedLinkedList_search (list, _this->data[i]) ;
			Timer_stop (_this->timer) ;
			searchTime += Timer_duration (_this->timer) ;
		}
		
		printf("\n크기: %d, 삽입하기: %d, 최소값찾기: %d , 최대값찾기: %d , 검색하기: %d", testSize, (long)insertTime, (long)minTime, (long)maxTime, (long)searchTime);
		UnsortedLinkedList_free (list) ;
	}
}

void  PerformanceMeasurement_testSortedLinkedList (PerformanceMeasurement * _this) 
{
	SortedLinkedList * list ;
	Element min, max ;
	int i, testCount, testSize ;
	Bool found ;
	double insertTime, minTime, maxTime, searchTime ;
	printf("\n[SortedLinkedList]") ;
	for ( testCount = 0 ; testCount < _this->numOfTests ; testCount++ ) 
	{
		testSize = _this->testSizes[testCount] ;
		list = SortedLinkedList_new() ;
		insertTime = minTime = maxTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;
			SortedLinkedList_insert (list, _this->data[i]) ;
			
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			
			min = SortedLinkedList_min (list) ;
			Timer_stop (_this->timer) ;
			minTime += Timer_duration (_this->timer) ;
			Timer_start (_this->timer) ;
			
			max = SortedLinkedList_max (list) ;
				
			Timer_stop (_this->timer) ;
			maxTime += Timer_duration (_this->timer) ;
			
		}
		searchTime = 0 ;
		
		for ( i = 0 ; i < testSize ; i++) 
		{
			Timer_start (_this->timer) ;
			found = SortedLinkedList_search (list, _this->data[i]) ;
			Timer_stop (_this->timer) ;
			searchTime += Timer_duration (_this->timer) ;
		}
		
		
		printf("\n크기: %d, 삽입하기: %d, 최소값찾기: %d , 최대값찾기: %d , 검색하기: %d", testSize, (long)insertTime, (long)minTime, (long)maxTime, (long)searchTime);
		SortedLinkedList_free (list) ;
	}
}

void PerformanceMeasurement_free(PerformanceMeasurement * _this)
{
	free(_this->data);
	free(_this->timer);
	free(_this->testSizes);
}