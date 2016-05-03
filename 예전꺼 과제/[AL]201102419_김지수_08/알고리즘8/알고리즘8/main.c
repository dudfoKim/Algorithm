#include "TestMinPQ.h"

#define NumOfTests 5
#define FirstTestSize 10000 // 첫번째 실험 데이터 크기
#define SizeIncrement 10000 // 실험 데이터 크기 증가량

void main()
{
	TestMinPQ * testMinPQ = TestMinPQ_new(NumOfTests, FirstTestSize, SizeIncrement) ;
	TestMinPQ_unsortedArray(testMinPQ) ;
	TestMinPQ_increasinglySortedArray(testMinPQ) ;
	TestMinPQ_decreasinglySortedArray(testMinPQ) ;
	TestMinPQ_minHeap(testMinPQ) ;
	TestMinPQ_free(testMinPQ) ;

}