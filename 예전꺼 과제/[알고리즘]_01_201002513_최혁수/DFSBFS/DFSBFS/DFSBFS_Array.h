#include <stdio.h>
#include <stdlib.h>
#define bool int
#define TRUE 1
#define FALSE 0

typedef struct queue *queue_pointer;  // BFS 구현을 위한 queue
typedef struct queue {
		int vertex;
		queue_pointer link;
};

int numofVertex;
int **Vertex_Array;    // 2차원 배열
bool *visited;          // bool 자료형 사용
int delete_queue(queue_pointer *);
void add_queue(queue_pointer *, queue_pointer *, int);
void dfs(int);
void bfs(int);
void createGraph(int);
void insertEdge(int, int);
void deleteVertex(int);
void printGraph();
void vertexInit();
