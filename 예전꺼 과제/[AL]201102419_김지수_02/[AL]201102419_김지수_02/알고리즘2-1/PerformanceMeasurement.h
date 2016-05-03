#include "Timer.h"
#include "Global.h"
#include "UnsortedArrayList.h"
#include "SortedArrayList.h"
#include "UnsortedLinkedList.h"
#include "SortedLinkedList.h"

#define MaxTestSize 10000
#define NumOfTests 5
#define FirstTestSize 1000 // ù��° ���� ������ ũ��
#define SizeIncrement 1000 // ���� ������ ũ�� ������

typedef struct _PerformanceMeasurement PerformanceMeasurement;

PerformanceMeasurement * PerformanceMeasurement_New();
void PerformanceMeasurement_free (PerformanceMeasurement * _this);
void PerformanceMeasurement_generateData (PerformanceMeasurement * _this);//���� ������ �ʿ��� �����͸� �����Ѵ�.
void PerformanceMeasurement_testUnsortedArray (PerformanceMeasurement * _this);//Unsorted Array�� ������ List�� ������ �����Ѵ�.
void PerformanceMeasurement_testSortedArray (PerformanceMeasurement * _this);//Sorted Array�� ������ List�� ������ �����Ѵ�.
void PerformanceMeasurement_testUnsortedLinkedList (PerformanceMeasurement * _this);//Unsorted Linked List�� ������ List�� ������ �����Ѵ�.
void PerformanceMeasurement_testSortedLinkedList (PerformanceMeasurement * _this);//Sorted Linked List�� ������ List�� ������ �����Ѵ�.
