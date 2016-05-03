#include <stdio.h>
#include <stdlib.h>

typedef struct _schedule{
	int index;  // �Է� ����
	int start;	 // ù ���۰�
	int finish;  // ����
	struct _schedule* next;  // ����Ʈ ����κ�
} schedule;

schedule* initNode(int, int);  // Init & Alloc
schedule* insertSchedule(int);  // Insert the jobs
schedule* intervalSchedule(schedule* );  // Sort & Find interval_scheduling
void printIntervalSchedule(schedule* );  // Print the schedule