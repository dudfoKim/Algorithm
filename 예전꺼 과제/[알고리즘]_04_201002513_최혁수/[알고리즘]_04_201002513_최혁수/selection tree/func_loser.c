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
/* run[][] �� ���� Loser Tree ���� */
void initSelectionTree(SelectionTree* sTree, SetOfRuns* runs)
{
	int i, j;
	int level3=4;   // �ܸ���� ù idx : 4
	int temp[2];    // sTree->tree[0], tree[1] �ӽ����� ��
	int f_num=0; 
	// sTree->tree[i].key & idx = 0 & -1 �� �ʱ�ȭ
	for(i=0; i<TREE_SIZE; i++){
		sTree->tree[i].key = 0;
		sTree->tree[i].idx = -1;
	}
	// run[][]�� ���� Loser Tree ���� 
	for(i=0; i<TREE_SIZE; i+=2){  // i+=2 : 2���� run[][]�� �񱳷� 1���� tree[]�� ����
		if(runs->run[i][0] > runs->run[i+1][0]){  // ù �ܸ���� ����
			sTree->tree[level3].key = runs->run[i][0];  // ���� ���� ����
			sTree->tree[level3].idx = i;
			// �θ��尡 ä���������鼭 �θ��尡 �ڽĳ�庸�� �۴ٸ�
			if(sTree->tree[level3/2].key !=0 && sTree->tree[level3/2].key < runs->run[i+1][0]){
				sTree->tree[level3/2].key = runs->run[i+1][0];  // �ڽĳ�带 �θ���� ������.
				sTree->tree[level3/2].idx = i+1;
				level3++;
			}
			// �θ��尡 ũ�ٸ� level3++�� skip
			else if(sTree->tree[level3/2].key != 0 && sTree->tree[level3/2].key > runs->run[i+1][0]){
				level3++;
			}
			else{ // �θ��尡 ��������� �ڽĳ�尪���� �ʱ�ȭ
			sTree->tree[level3/2].key = runs->run[i+1][0]; 
			sTree->tree[level3/2].idx = i+1;
			level3++;
			}
		}
		else{ // == if(runs->run[i][0] < runs->run[i+1][0]) �̸鼭, ���� ���� ������ ���Ѵ�.
			sTree->tree[level3].key = runs->run[i+1][0];
			sTree->tree[level3].idx = i+1;
			if(sTree->tree[level3/2].key != 0 && sTree->tree[level3/2].key < runs->run[i][0]){
				sTree->tree[level3/2].key = runs->run[i][0];
				sTree->tree[level3/2].idx = i;
				level3++;
			}
			else if(sTree->tree[level3/2].key != 0 && sTree->tree[level3/2].key > runs->run[i][0]){
				level3++;
			}
			else{
			sTree->tree[level3/2].key = runs->run[i][0];
			sTree->tree[level3/2].idx = i;
			level3++;
			}
		}
	}
	// ������ ���� run[][]�� idx ���� temp[2]�� ����
	// temp[2]�� ����� 2���� ������, tree[0] or tree[1] �� ä������.(�ּҰ� 2��)
	for(i=0; i<TREE_SIZE; i++)
	for(j=0; j<TREE_SIZE; j++){
		if(i==sTree->tree[j].idx)  break;
		else if(j==7) temp[f_num++]=i;
	}
	// temp[2]�� 2���� idx���� ����, �ΰ��� run[][]�� ���Ͽ� tree[0] or tree[1]�� ����.(.idx or .key)
	if(runs->run[temp[0]][0] > runs->run[temp[1]][0]){
		sTree->tree[0].key = runs->run[temp[1]][0];
		sTree->tree[0].idx = temp[1];
		sTree->tree[1].key = runs->run[temp[0]][0];
		sTree->tree[1].idx = temp[0];
	}
	else{
		sTree->tree[0].key = runs->run[temp[0]][0];
		sTree->tree[0].idx = temp[0];
		sTree->tree[1].key = runs->run[temp[1]][0];
		sTree->tree[1].idx = temp[1];
	}
}

/** �ֻ��� tree[0].key ���� return(���) �� Loser Tree �籸�� **/
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