#include "TestMinPQ.h"

struct _TestMinPQ 
{
	long numOfTests ; // 실험 회수 (각 구현 마다의)
	long firstTestSize ; // 첫 번째 실험의 크기
	long sizeIncrement ; // 실험 크기의 증가량
	Timer * timer ;
	RandomGen * randomGen ;
};

TestMinPQ * TestMinPQ_new (long numOfTests, long firstTestSize, long sizeIncrement)
{
	TestMinPQ * _this = NewObject(TestMinPQ) ; // 객체 생성
	_this ->numOfTests = numOfTests ; // 실험 회수 (각 구현 마다의)
	_this ->firstTestSize = firstTestSize ; // 첫 번째 실험의 크기
	_this ->sizeIncrement = sizeIncrement ; // 실험 크기의 증가량
	_this->timer = Timer_new() ;
	_this->randomGen = RandomGen_new() ;

	printf("< Min Priority Queue의 구현에 따른 실행 성능 차이 알아보기 >\n"); 

	return _this;
}
void TestMinPQ_free (TestMinPQ * _this)
{
	free(_this->randomGen);
	free(_this->timer);
	free(_this);
}

void TestMinPQ_unsortedArray (TestMinPQ * _this)
{
	UnsortedArrayPQ * minPQ ;
	long i, testCount, testSize ;
	long randomData, minElement ;
	double insertTime, deleteMinTime ;

	printf("[Unsorted Array]") ;

	for (testCount = 0, testSize = _this->firstTestSize ; testCount < _this->numOfTests ; testCount++, testSize += _this->sizeIncrement )
	{
		minPQ = UnsortedArrayPQ_new (testSize) ;
		insertTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			randomData = RandomGen_number(_this->randomGen) ;
			Timer_start (_this->timer) ;

			if ( ! UnsortedArrayPQ_isFull(minPQ) ) 
			{
				UnsortedArrayPQ_insert (minPQ, randomData) ;
			}
				
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
		}
		
		deleteMinTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;

			if ( ! UnsortedArrayPQ_isEmpty(minPQ) )
			{
				minElement = UnsortedArrayPQ_deleteMin (minPQ) ;
			}

			Timer_stop (_this->timer) ;
			deleteMinTime += Timer_duration (_this->timer) ;
		}
		
		printf ("\n크기: %d, 삽입하기: %d, 최소값삭제: %d ", testSize, (long) insertTime, (long) deleteMinTime ) ;
		UnsortedArrayPQ_free (minPQ) ;
	}
}

void TestMinPQ_increasinglySortedArray(TestMinPQ * _this) //오름차순의 sorted array로 구현된 min PQ의 성능을 측정한다.
{
	IncreasinglySortedArrayPQ * minPQ ;
	long i, testCount, testSize ;
	long randomData, minElement ;
	double insertTime, deleteMinTime ;

	printf("\n[IncreasinglySorted Array]") ;

	for (testCount = 0, testSize = _this->firstTestSize ; testCount < _this->numOfTests ; testCount++, testSize += _this->sizeIncrement )
	{
		minPQ = IncreasinglySortedArrayPQ_new (testSize) ;
		insertTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			randomData = RandomGen_number(_this->randomGen) ;
			Timer_start (_this->timer) ;

			if ( ! IncreasinglySortedArrayPQ_isFull(minPQ) ) 
			{
				IncreasinglySortedArrayPQ_insert (minPQ, randomData) ;
			}
				
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
		}
		
		deleteMinTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;

			if ( ! IncreasinglySortedArrayPQ_isEmpty(minPQ) )
			{
				minElement = IncreasinglySortedArrayPQ_deleteMin (minPQ) ;
			}

			Timer_stop (_this->timer) ;
			deleteMinTime += Timer_duration (_this->timer) ;
		}
		
		printf ("\n크기: %d, 삽입하기: %d, 최소값삭제: %d ", testSize, (long) insertTime, (long) deleteMinTime ) ;
		IncreasinglySortedArrayPQ_free (minPQ) ;
	}
}
void TestMinPQ_decreasinglySortedArray (TestMinPQ * _this) //내림차순의 sorted array로 구현된 min PQ의 성능을 측정한다.
{
	DecreasinglySortedArrayPQ * minPQ ;
	long i, testCount, testSize ;
	long randomData, minElement ;
	double insertTime, deleteMinTime ;

	printf("\n[DecreasinglySorted Array]") ;

	for (testCount = 0, testSize = _this->firstTestSize ; testCount < _this->numOfTests ; testCount++, testSize += _this->sizeIncrement )
	{
		minPQ = DecreasinglySortedArrayPQ_new (testSize) ;
		insertTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			randomData = RandomGen_number(_this->randomGen) ;
			Timer_start (_this->timer) ;

			if ( ! DecreasinglySortedArrayPQ_isFull(minPQ) ) 
			{
				DecreasinglySortedArrayPQ_insert (minPQ, randomData) ;
			}
				
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
		}
		
		deleteMinTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;

			if ( ! DecreasinglySortedArrayPQ_isEmpty(minPQ) )
			{
				minElement = DecreasinglySortedArrayPQ_deleteMin (minPQ) ;
			}

			Timer_stop (_this->timer) ;
			deleteMinTime += Timer_duration (_this->timer) ;
		}
		
		printf ("\n크기: %d, 삽입하기: %d, 최소값삭제: %d ", testSize, (long) insertTime, (long) deleteMinTime ) ;
		DecreasinglySortedArrayPQ_free (minPQ) ;
	}
}
void TestMinPQ_minHeap (TestMinPQ * _this) //Min heap으로 구현된 min PQ의 성능을 측정한다.
{
	MinHeapPQ * minPQ ;
	long i, testCount, testSize ;
	long randomData, minElement ;
	double insertTime, deleteMinTime ;

	printf("\n[MinHeapPQ]") ;

	for (testCount = 0, testSize = _this->firstTestSize ; testCount < _this->numOfTests ; testCount++, testSize += _this->sizeIncrement )
	{
		minPQ = MinHeapPQ_new (testSize+1) ;
		insertTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			randomData = RandomGen_number(_this->randomGen) ;
			Timer_start (_this->timer) ;

			if ( ! MinHeapPQ_isFull(minPQ) ) 
			{
				MinHeapPQ_insert (minPQ, randomData) ;
			}
				
			Timer_stop (_this->timer) ;
			insertTime += Timer_duration (_this->timer) ;
		}
		
		deleteMinTime = 0.0 ;

		for ( i = 0 ; i < testSize ; i++ ) 
		{
			Timer_start (_this->timer) ;

			if ( ! MinHeapPQ_isEmpty(minPQ) )
			{
				minElement = MinHeapPQ_deleteMin (minPQ) ;
			}

			Timer_stop (_this->timer) ;
			deleteMinTime += Timer_duration (_this->timer) ;
		}
		
		printf ("\n크기: %d, 삽입하기: %d, 최소값삭제: %d ", testSize, (long) insertTime, (long) deleteMinTime ) ;
		MinHeapPQ_free (minPQ) ;
	}

	printf("\n");
}



