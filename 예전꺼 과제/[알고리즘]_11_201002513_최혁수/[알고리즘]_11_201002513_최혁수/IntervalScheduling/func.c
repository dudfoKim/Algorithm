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

		add = initNode(i, start, finish);  // 입력받은 순으로 start-finish값을 매개변수로 노드생성

		/** schedule을 finish(끝나는 시점) 순으로 Sorting **/
		if ( interval_schedule == NULL )  // empty 상태일때 
			interval_schedule = add;  // 위에서 생성한 initNode()를 가리킨다.
		else 
			for ( target = interval_schedule ; ; target = target->next )  // schedule list를 검색
				if ( (interval_schedule->finish) > (add->finish) ){  // list내 첫 노드의 finish가 새로 입력받은 finish보다 크면
					add->next = interval_schedule;  // add의 링크로 interval_schedule 연결
					interval_schedule = add;  
					break;
				}
				else if ( target->next == NULL ){  // 끝 탐색까지 list내 finish가 add->finish보다 큰 값이 없다면
					target->next = add;  // 뒤에 링크연결
					break;
				}
				// list내 입력받은 finish보다 더 큰 finish를 가진 노드가 있으면
				else if ( (add->finish) < (target->next->finish) ){  
					add->next = target->next;  // add, target의 next를 add부분에 연결
					target->next = add;
					break;
				}
	}
	return interval_schedule;
}

schedule* intervalSchedule(schedule* interval_schedule){
	schedule *insert, *search, *add;
	// insert는 매개변수로 입력받은 schedule list내 첫 노드의 데이터를 기준으로 생성된 node(=node copy)
	insert = initNode(interval_schedule->index, interval_schedule->start, interval_schedule->finish);
	// 첫 값을 기준으로 interval_schedule list내 insert->finish보다 finish가 큰 것을 찾아 add라는 포인터에 순차적으로 연결i
	// 이는 결국 finish를 기준으로 기존 무정렬의 jobs를 끊어 정렬하여 insert로 표현
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
	// interval scheduling 된 리스트를 순차적으로 출력
	for ( print = interval_search ; print ; print = print->next )
		printf("Index : %d, Interval : <%3d, %3d>\n", print->index, print->start, print->finish);
	printf("Interval Scheduling을 종료합니다.\n");
}