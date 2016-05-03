#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TREE_SIZE 8 // Ʈ�� �� �� ������
#define MAX_KEY 10000 // ���� ���� �ִ� Ű�� �ִ밪
typedef struct _treeNode // Selection Tree�� ���
{
int key; // node�� key
int idx; // node�� Ű���� ��ġ�ϴ� run�� ��ȣ
} treeNode;
typedef struct _SelectionTree // Selection Tree ����ü
{
treeNode tree[TREE_SIZE]; // Tree�� ��Ÿ�� �迭
} SelectionTree;
typedef struct _SetOfRuns // run���� ����ü
{
int run[TREE_SIZE][TREE_SIZE];
//int topOfRuns[TREE_SIZE];   ��� ���� �Լ�
} SetOfRuns;
// Run�� �ʱ�ȭ�Ѵ�.
// run�� ������ ���� ä���. �� ������ sort�� ���� ä���.
void initRuns(SetOfRuns* runs);
// SelectionTree�� �ʱ�ȭ �Ѵ�.
// �� ���� ù��° ��带 ������ SelectionTree�� �����Ѵ�.
void initSelectionTree(SelectionTree* sTree, SetOfRuns* runs);
//SelectionTree�� �̿��Ͽ� run���� ���� ���� Key�� �ϳ��� �����Ѵ�.
//���ÿ� SelectionTree�� �籸���Ѵ�.
//���� run�� �����ִ� ��尡 ���ٸ� MAX_KEY�� �����Ѵ�.
int getWinner(SelectionTree* sTree, SetOfRuns* runs);
//SelectionTree�� ����Ѵ�.
void printTree(SelectionTree* sTree);
//���� run�� �����ִ� ����� Ű���� ������ ���·� ����Ѵ�.
void printRuns(SetOfRuns* runs);