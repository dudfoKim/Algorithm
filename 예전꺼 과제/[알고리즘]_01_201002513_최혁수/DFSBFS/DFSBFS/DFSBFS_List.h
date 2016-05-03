#include <stdio.h>
#include <stdlib.h>
#define bool int  // bool 자료형 재정의(c에서 boolean 자료형은 c99부터 제공)
#define TRUE 1
#define FALSE 0
typedef struct node *pnode;
struct node {
	int vertex;             // 인접한 vertex 값을 저장
	struct node *link;    // 인접한 vertex 를 가리키는 포인터
};
typedef struct queue *queue_pointer;
typedef struct queue {
		int vertex;               // 인접한 vertex 값을 저장
		queue_pointer link;   // 인접한 queue 를 가리키는 포인터   
};
pnode* headNodes;
int numofVertex;               // 정점의 갯수를 저장
bool *visited;                   // 방문된 정점을 표기
void createGraph(int);         // Graph를 생성
void insertEdge(int, int);      // 정점간에 간선을 연결해준다(=노드를 연결)
void deleteVertex(int);         // 정점을 삭제
void printGraph();              // 그래프 출력
void vertexInit();                // 방문된 정점표기 초기화

void dfs(int);                    // dfs 구현
void bfs(int);                    // bfs 구현
void add_queue(queue_pointer *, queue_pointer *, int);   // 큐값에 정점을 저장(push 기능)
int delete_queue(queue_pointer *);                            // pop() 기능

