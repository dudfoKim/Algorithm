#pragma once
#include "Global.h"
#include "UnsortedArrayPQ.h"
#include "DecreasinglySortedArrayPQ.h"
#include "IncreasinglySortedArrayPQ.h"
#include "MinHeapPQ.h"
#include "Timer.h"
#include "RandomGen.h"

#define ProbabilityForInsert 0.5

typedef struct _TestMinPQ TestMinPQ;//공개 함수



TestMinPQ * TestMinPQ_new (long numOfTests, long firstTestSize, long sizeIncrement) ;
void TestMinPQ_free (TestMinPQ * _this) ;
void TestMinPQ_unsortedArray (TestMinPQ * _this) ;//Unsorted Array로 구현된 min PQ의 성능을 측정한다.
void TestMinPQ_increasinglySortedArray(TestMinPQ * _this) ;//오름차순의 sorted array로 구현된 min PQ의 성능을 측정한다.
void TestMinPQ_decreasinglySortedArray (TestMinPQ * _this) ;//내림차순의 sorted array로 구현된 min PQ의 성능을 측정한다.
void TestMinPQ_minHeap (TestMinPQ * _this) ;//Min heap으로 구현된 min PQ의 성능을 측정한다.