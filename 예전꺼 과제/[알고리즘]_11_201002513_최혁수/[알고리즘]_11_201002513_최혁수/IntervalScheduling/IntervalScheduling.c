#include "head.h"

int main(void){
	int num;
	schedule *interval_schedule, *interval_search;

	printf("Input interval numbers : ");

	scanf("%d", &num);

	interval_schedule = insertSchedule(num);
	
	interval_search = intervalSchedule(interval_schedule);

	printIntervalSchedule(interval_search);

	return 0;
}
