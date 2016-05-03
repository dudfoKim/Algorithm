#include "head.h"

schedule* initNode(int index, int start, int finish){  // Init & Alloc node
	schedule *temp;
	temp = (schedule*)malloc(sizeof(schedule));
	temp->index = index;
	temp->start = start;
	temp->finish = finish;
	temp->next = NULL;

	return temp;
}

schedule* insertSchedule(int num){
	int i, start, finish;
	schedule *interval_schedule=NULL, *target, *add;

	for ( i = 0 ; i < num ; i++ ){
		printf("Input each intervals startTime finishTime : ");
		scanf("%d %d", &start, &finish);
		fflush(stdin);

		add = initNode(i, start, finish);  // �Է¹��� ������ start-finish���� �Ű������� ������

		/** schedule�� finish(������ ����) ������ Sorting **/
		if ( interval_schedule == NULL )  // empty �����϶� 
			interval_schedule = add;  // ������ ������ initNode()�� ����Ų��.
		else 
			for ( target = interval_schedule ; ; target = target->next )  // schedule list�� �˻�
				if ( (interval_schedule->finish) > (add->finish) ){  // list�� ù ����� finish�� ���� �Է¹��� finish���� ũ��
					add->next = interval_schedule;  // add�� ��ũ�� interval_schedule ����
					interval_schedule = add;  
					break;
				}
				else if ( target->next == NULL ){  // �� Ž������ list�� finish�� add->finish���� ū ���� ���ٸ�
					target->next = add;  // �ڿ� ��ũ����
					break;
				}
				// list�� �Է¹��� finish���� �� ū finish�� ���� ��尡 ������
				else if ( (add->finish) < (target->next->finish) ){  
					add->next = target->next;  // add, target�� next�� add�κп� ����
					target->next = add;
					break;
				}
	}
	return interval_schedule;
}

schedule* intervalSchedule(schedule* interval_schedule){
	schedule *insert, *search, *add;
	// insert�� �Ű������� �Է¹��� schedule list�� ù ����� �����͸� �������� ������ node(=node copy)
	insert = initNode(interval_schedule->index, interval_schedule->start, interval_schedule->finish);
	// ù ���� �������� interval_schedule list�� insert->finish���� finish�� ū ���� ã�� add��� �����Ϳ� ���������� ����i
	// �̴� �ᱹ finish�� �������� ���� �������� jobs�� ���� �����Ͽ� insert�� ǥ��
	for ( search = interval_schedule->next ; search != NULL ; search = search->next ){
		if ( insert->finish <= search->start ){
			add = initNode(search->index, search->start, search->finish);
			add->next = insert;
			insert = add;
		}
	}
	return insert;
}

void printIntervalSchedule(schedule* interval_search){
	schedule *print;
	// interval scheduling �� ����Ʈ�� ���������� ���
	for ( print = interval_search ; print ; print = print->next )
		printf("Index : %d, Interval : <%3d, %3d>\n", print->index, print->start, print->finish);
	printf("Interval Scheduling�� �����մϴ�.\n");
}