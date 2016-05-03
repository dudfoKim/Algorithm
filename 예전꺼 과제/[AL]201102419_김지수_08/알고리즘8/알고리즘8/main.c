#include "TestMinPQ.h"

#define NumOfTests 5
#define FirstTestSize 10000 // ù��° ���� ������ ũ��
#define SizeIncrement 10000 // ���� ������ ũ�� ������

void main()
{
	TestMinPQ * testMinPQ = TestMinPQ_new(NumOfTests, FirstTestSize, SizeIncrement) ;
	TestMinPQ_unsortedArray(testMinPQ) ;
	TestMinPQ_increasinglySortedArray(testMinPQ) ;
	TestMinPQ_decreasinglySortedArray(testMinPQ) ;
	TestMinPQ_minHeap(testMinPQ) ;
	TestMinPQ_free(testMinPQ) ;

}