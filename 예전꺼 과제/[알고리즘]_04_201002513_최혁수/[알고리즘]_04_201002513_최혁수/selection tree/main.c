#include "head.h"

void main()
{
	SelectionTree sTree;
	SetOfRuns runs;
	int i,j;
	// Runs, SelectionTree의 초기화
	initRuns(&runs);
	initSelectionTree(&sTree, &runs);
	// 초기 SelectionTree/Run 상태 출력
	printf("============= SelectionTree View ==============\n");
	printTree(&sTree);
	printRuns(&runs);
	// 정렬된 순서로 run의 레코드를 모두 출력
	printf("===============================================\n");
	j=0;
	// 실행결과 1번
	while( (i = getWinner(&sTree, &runs)) != MAX_KEY)
	{
		printf("%4d ", i);
		if(j%10==9)
			printf("\n");
		j++;
	}
	printf("\n");
	
	/*
	//실행 결과 2번 : 32번 getWinner 출력 후  Tree & Runs 출력
	
	for(i=0; i<32; i++){
		printf("%4d ",getWinner(&sTree, &runs));
		if(i%10==9) printf("\n");
	}
	printf("\n");
	printf("============= SelectionTree View ==============\n");
	printTree(&sTree);
	printRuns(&runs);
	*/
}