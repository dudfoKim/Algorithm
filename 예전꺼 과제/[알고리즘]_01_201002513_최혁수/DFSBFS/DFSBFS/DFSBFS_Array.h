#include <stdio.h>
#include <stdlib.h>
#define bool int
#define TRUE 1
#define FALSE 0

typedef struct queue *queue_pointer;  // BFS ������ ���� queue
typedef struct queue {
		int vertex;
		queue_pointer link;
};

int numofVertex;
int **Vertex_Array;    // 2���� �迭
bool *visited;          // bool �ڷ��� ���
int delete_queue(queue_pointer *);
void add_queue(queue_pointer *, queue_pointer *, int);
void dfs(int);
void bfs(int);
void createGraph(int);
void insertEdge(int, int);
void deleteVertex(int);
void printGraph();
void vertexInit();
