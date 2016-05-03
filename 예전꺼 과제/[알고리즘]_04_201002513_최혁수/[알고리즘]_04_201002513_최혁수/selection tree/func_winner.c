#include "head.h"
/** runs �ʱ�ȭ : ������ ���� �������� **/
void initRuns(SetOfRuns* runs){
	int i, j, k;
	int temp;
	srand((unsigned)time(NULL));
	
	for(i=0; i<TREE_SIZE; i++)
	for(j=0; j<TREE_SIZE; j++)
	runs->run[i][j] = rand()%10000;  // MAX_KEY ���� ���� ������ �������� run[][] ����

	/** ���� ���Ŀ� ���� run[][] �������� ���� **/
	for(k=0; k<TREE_SIZE; k++)
	for(i=0; i<TREE_SIZE; i++)
	for(j=i+1; j<TREE_SIZE; j++){
		if(runs->run[k][i] > runs->run[k][j]){
		temp = runs->run[k][i];
		runs->run[k][i] = runs->run[k][j];
		runs->run[k][j] = temp;
		}
	}
}
/* run[][] �� ���� Winner Tree ���� */
void initSelectionTree(SelectionTree* sTree, SetOfRuns* runs){
	int i;
	int level3 = 4;  // �ܸ���� ù idx : 4
	// sTree->tree[i].key & idx = 0 & -1 �� �ʱ�ȭ
	for(i=0; i<TREE_SIZE; i++){
		sTree->tree[i].key = 0;
		sTree->tree[i].idx = -1;
	}
	// run[][]�� ���� Winner Tree ���� 
	// �ܸ����(Terminal node)�� �ʱ�ȭ
	for(i=0; i<TREE_SIZE; i+=2){
		if(runs->run[i][0] < runs->run[i+1][0]){
		sTree->tree[level3].key = runs->run[i][0];
		sTree->tree[level3].idx = i;
		level3++;
		}
		else{
		sTree->tree[level3].key = runs->run[i+1][0];
		sTree->tree[level3].idx = i+1;
		level3++;
		}
	}
	// �ܸ����(Terminal node), �� �ڽĳ��(children)���� �񱳸� ���� �θ��� �ʱ�ȭ
	for(i=4; i<TREE_SIZE; i+=2){
		if(sTree->tree[i].key < sTree->tree[i+1].key){
			sTree->tree[i/2].key = sTree->tree[i].key;
			sTree->tree[i/2].idx = sTree->tree[i].idx;
		}
		else{
			sTree->tree[i/2].key = sTree->tree[i+1].key;
			sTree->tree[i/2].idx = sTree->tree[i+1].idx;
		}
	}
	// �ڽĳ��(children)���� �񱳸� ���� �θ��� �ʱ�ȭ
	if(sTree->tree[2].key < sTree->tree[3].key){
			sTree->tree[1].key = sTree->tree[2].key;
			sTree->tree[1].idx = sTree->tree[2].idx;
	}
	else{
			sTree->tree[1].key = sTree->tree[3].key;
			sTree->tree[1].idx = sTree->tree[3].idx;
	}
	// ������Ͽ� ���õ� tree[]�� ������ ä��� ���� tree[0]�� �����ִ�.
	sTree->tree[0].key = sTree->tree[1].key;
	sTree->tree[0].idx = sTree->tree[1].idx;
}

/** �ֻ��� tree[0].key ���� return(���) �� Winner Tree �籸�� **/
int getWinner(SelectionTree* sTree, SetOfRuns* runs){
	int i;
	int temp = sTree->tree[0].key; // initSelectionTree()�� Root ��带 �ӽ�����
	for(i=0; i<TREE_SIZE-1; i++){   // run[][] �籸��
		runs->run[sTree->tree[0].idx][i] = runs->run[sTree->tree[0].idx][i+1];
	}
	// �ֻ��� Root ��忡 ����� idx�� �̿��� run[idx][7] ���� MAX_KEY ����.
	runs->run[sTree->tree[0].idx][TREE_SIZE-1] = MAX_KEY;
	initSelectionTree(sTree, runs); // �籸���� run[][]�� �̿��� Loser Tree �籸��
	return temp; // �ӽ� ����� temp�� return(���)
}
/** Expression Tree **/
void printTree(SelectionTree* sTree){
	printf("                              %d                      \n",sTree->tree[0].key);
	printf("                              %d                      \n",sTree->tree[1].key);
	printf("              %d                         %d         \n",sTree->tree[2].key,sTree->tree[3].key);
	printf("       %d           %d           %d            %d    \n",sTree->tree[4].key,sTree->tree[5].key,sTree->tree[6].key,sTree->tree[7].key);
}
/** Expression Run **/
void printRuns(SetOfRuns* runs){
	int i, j;
	for(i=0; i<TREE_SIZE; i++){
	for(j=0; j<TREE_SIZE; j++){
	printf("%d\t  " , runs->run[j][i]);
	}
	printf("\n");
	}
	printf("\n");
}