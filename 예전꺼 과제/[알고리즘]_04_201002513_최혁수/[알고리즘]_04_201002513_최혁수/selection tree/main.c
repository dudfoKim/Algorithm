#include "head.h"

void main()
{
	SelectionTree sTree;
	SetOfRuns runs;
	int i,j;
	// Runs, SelectionTree�� �ʱ�ȭ
	initRuns(&runs);
	initSelectionTree(&sTree, &runs);
	// �ʱ� SelectionTree/Run ���� ���
	printf("============= SelectionTree View ==============\n");
	printTree(&sTree);
	printRuns(&runs);
	// ���ĵ� ������ run�� ���ڵ带 ��� ���
	printf("===============================================\n");
	j=0;
	// ������ 1��
	while( (i = getWinner(&sTree, &runs)) != MAX_KEY)
	{
		printf("%4d ", i);
		if(j%10==9)
			printf("\n");
		j++;
	}
	printf("\n");
	
	/*
	//���� ��� 2�� : 32�� getWinner ��� ��  Tree & Runs ���
	
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