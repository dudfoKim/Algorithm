#include <stdio.h>
#include "PerformanceMeasurement.h"

void main()
{
	
	PerformanceMeasurement* pmList;
	printf("인텔과 AMD 값이 다릅니다. 예를들어값이 바로나오는 sorted Array가 인텔시스템에선 60~70이고 AMD시스템에선 1000정도 나오네요");
	
	pmList = PerformanceMeasurement_New();

	PerformanceMeasurement_generateData(pmList);
	
	PerformanceMeasurement_testUnsortedArray(pmList);

	PerformanceMeasurement_testSortedArray(pmList);
	PerformanceMeasurement_testUnsortedLinkedList(pmList);
	PerformanceMeasurement_testSortedLinkedList(pmList);
	PerformanceMeasurement_free(pmList);
}