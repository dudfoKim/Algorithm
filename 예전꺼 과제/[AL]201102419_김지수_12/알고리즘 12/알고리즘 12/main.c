#include "IntervalSchedule.h"

int main()
{
	IntervalSchedule * schedule ;
	schedule = IntervalSchedule_new();
	
	if (! IntervalSchedule_inputIntervals(schedule)) 
	{
		printf("오류: 구간이 적절하게 입력되지 않았습니다. 프로그램을 종료합니다.\n");
	}
	else 
	{
		IntervalSchedule_runGreedy(schedule);
		IntervalSchedule_showResults(schedule);
	}
	
	IntervalSchedule_free(schedule);
	printf("Interval Scheduling을 종료합니다.\n");

	return 0;
}