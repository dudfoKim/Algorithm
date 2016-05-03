#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TREE_SIZE 8 // 트리 및 런 사이즈
#define MAX_KEY 10000 // 런에 들어갈수 있는 키의 최대값
typedef struct _treeNode // Selection Tree의 노드
{
int key; // node의 key
int idx; // node의 키값이 위치하는 run의 번호
} treeNode;
typedef struct _SelectionTree // Selection Tree 구조체
{
treeNode tree[TREE_SIZE]; // Tree를 나타낼 배열
} SelectionTree;
typedef struct _SetOfRuns // run들의 구조체
{
int run[TREE_SIZE][TREE_SIZE];
//int topOfRuns[TREE_SIZE];   사용 안한 함수
} SetOfRuns;
// Run을 초기화한다.
// run에 임의의 값을 채운다. 각 런마다 sort된 값을 채운다.
void initRuns(SetOfRuns* runs);
// SelectionTree를 초기화 한다.
// 각 런의 첫번째 노드를 가지고 SelectionTree를 구성한다.
void initSelectionTree(SelectionTree* sTree, SetOfRuns* runs);
//SelectionTree를 이용하여 run에서 가장 작은 Key값 하나를 리턴한다.
//동시에 SelectionTree를 재구성한다.
//만약 run에 남아있는 노드가 없다면 MAX_KEY를 리턴한다.
int getWinner(SelectionTree* sTree, SetOfRuns* runs);
//SelectionTree를 출력한다.
void printTree(SelectionTree* sTree);
//현재 run에 남아있는 노드의 키값을 적당한 형태로 출력한다.
void printRuns(SetOfRuns* runs);