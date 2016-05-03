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
/* run[][] 에 의한 Loser Tree 구성 */
void initSelectionTree(SelectionTree* sTree, SetOfRuns* runs)
{
	int i, j;
	int level3=4;   // 단말노드 첫 idx : 4
	int temp[2];    // sTree->tree[0], tree[1] 임시저장 값
	int f_num=0; 
	// sTree->tree[i].key & idx = 0 & -1 로 초기화
	for(i=0; i<TREE_SIZE; i++){
		sTree->tree[i].key = 0;
		sTree->tree[i].idx = -1;
	}
	// run[][]에 의한 Loser Tree 구성 
	for(i=0; i<TREE_SIZE; i+=2){  // i+=2 : 2개의 run[][]의 비교로 1개의 tree[]를 구성
		if(runs->run[i][0] > runs->run[i+1][0]){  // 첫 단말노드 구성
			sTree->tree[level3].key = runs->run[i][0];  // 작은 값을 저장
			sTree->tree[level3].idx = i;
			// 부모노드가 채워져있으면서 부모노드가 자식노드보다 작다면
			if(sTree->tree[level3/2].key !=0 && sTree->tree[level3/2].key < runs->run[i+1][0]){
				sTree->tree[level3/2].key = runs->run[i+1][0];  // 자식노드를 부모노드로 보낸다.
				sTree->tree[level3/2].idx = i+1;
				level3++;
			}
			// 부모노드가 크다면 level3++로 skip
			else if(sTree->tree[level3/2].key != 0 && sTree->tree[level3/2].key > runs->run[i+1][0]){
				level3++;
			}
			else{ // 부모노드가 비어있을때 자식노드값으로 초기화
			sTree->tree[level3/2].key = runs->run[i+1][0]; 
			sTree->tree[level3/2].idx = i+1;
			level3++;
			}
		}
		else{ // == if(runs->run[i][0] < runs->run[i+1][0]) 이면서, 위와 같은 조건을 취한다.
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
	// 쓰이지 않은 run[][]의 idx 값을 temp[2]에 저장
	// temp[2]에 저장된 2개의 정보는, tree[0] or tree[1] 에 채워진다.(최소값 2개)
	for(i=0; i<TREE_SIZE; i++)
	for(j=0; j<TREE_SIZE; j++){
		if(i==sTree->tree[j].idx)  break;
		else if(j==7) temp[f_num++]=i;
	}
	// temp[2]의 2개의 idx값을 통해, 두개의 run[][]을 비교하여 tree[0] or tree[1]에 저장.(.idx or .key)
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

/** 최상위 tree[0].key 값을 return(출력) 및 Loser Tree 재구성 **/
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