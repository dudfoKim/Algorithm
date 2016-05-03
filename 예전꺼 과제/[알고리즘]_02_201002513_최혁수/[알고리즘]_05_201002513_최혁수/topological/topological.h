#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10  // �ִ� ������ ���� 10�� ����

typedef struct node *node_pointer;
typedef struct node{
		int vertex;
		struct node* link;
} node;

typedef struct headNode{
	int count;       // indegree count
	node *link;     // headnode[] �� ����� ���
}headNode;  

headNode graph[MAX_VERTEX];   // 10ũ���� graph ����

void initGraph(int);  // �ʱ�ȭ
void insertEdge();   // ��������
void createGraph(int, int);  // �׷��� ����
void topologicalOrder(int); // �������� �� ���
void printGraph(int);        // �׷��� ���