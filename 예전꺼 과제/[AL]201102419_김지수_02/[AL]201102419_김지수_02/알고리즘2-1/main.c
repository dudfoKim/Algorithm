#include <stdio.h>
#include "PerformanceMeasurement.h"

void main()
{
	
	PerformanceMeasurement* pmList;
	printf("���ڰ� AMD ���� �ٸ��ϴ�. �������� �ٷγ����� sorted Array�� ���ڽý��ۿ��� 60~70�̰� AMD�ý��ۿ��� 1000���� �����׿�");
	
	pmList = PerformanceMeasurement_New();

	PerformanceMeasurement_generateData(pmList);
	
	PerformanceMeasurement_testUnsortedArray(pmList);

	PerformanceMeasurement_testSortedArray(pmList);
	PerformanceMeasurement_testUnsortedLinkedList(pmList);
	PerformanceMeasurement_testSortedLinkedList(pmList);
	PerformanceMeasurement_free(pmList);
}