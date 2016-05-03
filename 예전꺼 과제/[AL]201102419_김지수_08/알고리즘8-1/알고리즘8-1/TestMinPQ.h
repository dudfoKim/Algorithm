#pragma once
#include "Global.h"
#include "UnsortedArrayPQ.h"
#include "DecreasinglySortedArrayPQ.h"
#include "IncreasinglySortedArrayPQ.h"
#include "MinHeapPQ.h"
#include "Timer.h"
#include "RandomGen.h"

#define ProbabilityForInsert 0.5

typedef struct _TestMinPQ TestMinPQ;//���� �Լ�



TestMinPQ * TestMinPQ_new (long numOfTests, long firstTestSize, long sizeIncrement) ;
void TestMinPQ_free (TestMinPQ * _this) ;
void TestMinPQ_unsortedArray (TestMinPQ * _this) ;//Unsorted Array�� ������ min PQ�� ������ �����Ѵ�.
void TestMinPQ_increasinglySortedArray(TestMinPQ * _this) ;//���������� sorted array�� ������ min PQ�� ������ �����Ѵ�.
void TestMinPQ_decreasinglySortedArray (TestMinPQ * _this) ;//���������� sorted array�� ������ min PQ�� ������ �����Ѵ�.
void TestMinPQ_minHeap (TestMinPQ * _this) ;//Min heap���� ������ min PQ�� ������ �����Ѵ�.