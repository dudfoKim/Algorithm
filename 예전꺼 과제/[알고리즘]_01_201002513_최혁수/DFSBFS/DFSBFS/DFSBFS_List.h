#include <stdio.h>
#include <stdlib.h>
#define bool int  // bool �ڷ��� ������(c���� boolean �ڷ����� c99���� ����)
#define TRUE 1
#define FALSE 0
typedef struct node *pnode;
struct node {
	int vertex;             // ������ vertex ���� ����
	struct node *link;    // ������ vertex �� ����Ű�� ������
};
typedef struct queue *queue_pointer;
typedef struct queue {
		int vertex;               // ������ vertex ���� ����
		queue_pointer link;   // ������ queue �� ����Ű�� ������   
};
pnode* headNodes;
int numofVertex;               // ������ ������ ����
bool *visited;                   // �湮�� ������ ǥ��
void createGraph(int);         // Graph�� ����
void insertEdge(int, int);      // �������� ������ �������ش�(=��带 ����)
void deleteVertex(int);         // ������ ����
void printGraph();              // �׷��� ���
void vertexInit();                // �湮�� ����ǥ�� �ʱ�ȭ

void dfs(int);                    // dfs ����
void bfs(int);                    // bfs ����
void add_queue(queue_pointer *, queue_pointer *, int);   // ť���� ������ ����(push ���)
int delete_queue(queue_pointer *);                            // pop() ���

