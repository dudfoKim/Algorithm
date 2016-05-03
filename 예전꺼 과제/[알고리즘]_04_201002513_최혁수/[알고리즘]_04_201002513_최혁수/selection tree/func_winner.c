#include "head.h"
/** runs 초기화 : 난수에 대한 오름차순 **/
void initRuns(SetOfRuns* runs){
	int i, j, k;
	int temp;
	srand((unsigned)time(NULL));
	
	for(i=0; i<TREE_SIZE; i++)
	for(j=0; j<TREE_SIZE; j++)
	runs->run[i][j] = rand()%10000;  // MAX_KEY 보다 작은 난수를 무작위로 run[][] 저장

	/** 버블 정렬에 의한 run[][] 오름차순 정렬 **/
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
/* run[][] 에 의한 Winner Tree 구성 */
void initSelectionTree(SelectionTree* sTree, SetOfRuns* runs){
	int i;
	int level3 = 4;  // 단말노드 첫 idx : 4
	// sTree->tree[i].key & idx = 0 & -1 로 초기화
	for(i=0; i<TREE_SIZE; i++){
		sTree->tree[i].key = 0;
		sTree->tree[i].idx = -1;
	}
	// run[][]에 의한 Winner Tree 구성 
	// 단말노드(Terminal node)를 초기화
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
	// 단말노드(Terminal node), 즉 자식노드(children)간의 비교를 통해 부모노드 초기화
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
	// 자식노드(children)간의 비교를 통해 부모노드 초기화
	if(sTree->tree[2].key < sTree->tree[3].key){
			sTree->tree[1].key = sTree->tree[2].key;
			sTree->tree[1].idx = sTree->tree[2].idx;
	}
	else{
			sTree->tree[1].key = sTree->tree[3].key;
			sTree->tree[1].idx = sTree->tree[3].idx;
	}
	// 헤더파일에 제시된 tree[]의 갯수를 채우기 위해 tree[0]를 쓰고있다.
	sTree->tree[0].key = sTree->tree[1].key;
	sTree->tree[0].idx = sTree->tree[1].idx;
}

/** 최상위 tree[0].key 값을 return(출력) 및 Winner Tree 재구성 **/
int getWinner(SelectionTree* sTree, SetOfRuns* runs){
	int i;
	int temp = sTree->tree[0].key; // initSelectionTree()의 Root 노드를 임시저장
	for(i=0; i<TREE_SIZE-1; i++){   // run[][] 재구성
		runs->run[sTree->tree[0].idx][i] = runs->run[sTree->tree[0].idx][i+1];
	}
	// 최상위 Root 노드에 저장된 idx를 이용해 run[idx][7] 값에 MAX_KEY 저장.
	runs->run[sTree->tree[0].idx][TREE_SIZE-1] = MAX_KEY;
	initSelectionTree(sTree, runs); // 재구성된 run[][]을 이용한 Loser Tree 재구성
	return temp; // 임시 저장된 temp값 return(출력)
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