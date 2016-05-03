#include <stdio.h>
#include <stdlib.h>

typedef struct _schedule{
	int index;  // 입력 순서
	int start;	 // 첫 시작값
	int finish;  // 끝값
	struct _schedule* next;  // 리스트 연결부분
} schedule;

schedule* initNode(int, int);  // Init & Alloc
schedule* insertSchedule(int);  // Insert the jobs
schedule* intervalSchedule(schedule* );  // Sort & Find interval_scheduling
void printIntervalSchedule(schedule* );  // Print the schedule