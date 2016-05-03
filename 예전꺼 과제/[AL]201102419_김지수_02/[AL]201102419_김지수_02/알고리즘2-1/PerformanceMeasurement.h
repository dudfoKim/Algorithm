#include "Timer.h"
#include "Global.h"
#include "UnsortedArrayList.h"
#include "SortedArrayList.h"
#include "UnsortedLinkedList.h"
#include "SortedLinkedList.h"

#define MaxTestSize 10000
#define NumOfTests 5
#define FirstTestSize 1000 // 첫번째 실험 데이터 크기
#define SizeIncrement 1000 // 실험 데이터 크기 증가량

typedef struct _PerformanceMeasurement PerformanceMeasurement;

PerformanceMeasurement * PerformanceMeasurement_New();
void PerformanceMeasurement_free (PerformanceMeasurement * _this);
void PerformanceMeasurement_generateData (PerformanceMeasurement * _this);//성능 측정에 필요한 데이터를 생성한다.
void PerformanceMeasurement_testUnsortedArray (PerformanceMeasurement * _this);//Unsorted Array로 구현한 List의 성능을 측정한다.
void PerformanceMeasurement_testSortedArray (PerformanceMeasurement * _this);//Sorted Array로 구현한 List의 성능을 측정한다.
void PerformanceMeasurement_testUnsortedLinkedList (PerformanceMeasurement * _this);//Unsorted Linked List로 구현한 List의 성능을 측정한다.
void PerformanceMeasurement_testSortedLinkedList (PerformanceMeasurement * _this);//Sorted Linked List로 구현한 List의 성능을 측정한다.
