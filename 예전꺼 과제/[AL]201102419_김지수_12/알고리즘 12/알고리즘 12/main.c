#include "IntervalSchedule.h"

int main()
{
	IntervalSchedule * schedule ;
	schedule = IntervalSchedule_new();
	
	if (! IntervalSchedule_inputIntervals(schedule)) 
	{
		printf("����: ������ �����ϰ� �Էµ��� �ʾҽ��ϴ�. ���α׷��� �����մϴ�.\n");
	}
	else 
	{
		IntervalSchedule_runGreedy(schedule);
		IntervalSchedule_showResults(schedule);
	}
	
	IntervalSchedule_free(schedule);
	printf("Interval Scheduling�� �����մϴ�.\n");

	return 0;
}