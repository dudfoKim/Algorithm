#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10  // 최대 정점의 갯수 10로 정의

typedef struct node *node_pointer;
typedef struct node{
		int vertex;
		struct node* link;
} node;

typedef struct headNode{
	int count;       // indegree count
	node *link;     // headnode[] 에 연결된 노드
}headNode;  

headNode graph[MAX_VERTEX];   // 10크기의 graph 생성

void initGraph(int);  // 초기화
void insertEdge();   // 정점연결
void createGraph(int, int);  // 그래프 생성
void topologicalOrder(int); // 위상정렬 및 출력
void printGraph(int);        // 그래프 출력