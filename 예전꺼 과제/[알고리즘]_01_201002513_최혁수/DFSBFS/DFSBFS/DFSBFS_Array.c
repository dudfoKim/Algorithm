#include "DFSBFS_Array.h"

void createGraph(int numVertex){
	int i=0, j=0;
	numofVertex = numVertex;
	Vertex_Array = (int**)malloc(sizeof(int)*(numVertex));
	for(i=0; i<numVertex ; i++)  Vertex_Array[i] = (int*)malloc(sizeof(int)*(numVertex));	

	for(i=0; i<numVertex; i++)
	for(j=0; j<numVertex; j++) Vertex_Array[i][j] = 0;
	
		visited = (int*)malloc(sizeof(int)*numofVertex);
		for(i=0; i<numofVertex; i++) visited[i] = 0;
}

void vertexInit(){
	int i;
		for(i=0; i<numofVertex; i++) visited[i] = 0;
}
void insertEdge(int v1, int v2){
	Vertex_Array[v1][v2] = 1;
}

void deleteVertex(int Vertex){
	int i=0, j=0;
	for(i=0; i<numofVertex; i++){
		Vertex_Array[Vertex][i]=0;
		Vertex_Array[i][Vertex]=0;
	}
}
void printGraph()
{
	int i=0, j=0;
	printf("    ");
	for(i=0; i<numofVertex; i++)
	printf("[%d] ",i);
	printf("\n");
	for(i=0; i<numofVertex; i++)
	{
		printf("[%d]  ",i);
		for(j=0; j<numofVertex; j++){
			printf("%d   ",Vertex_Array[i][j]);
		}
		printf("\n");
	}
}

void dfs(int v)
{
	int i;
	printf("%d ", v);
	visited[v] = 1; // 정점 v를 방문했다고 표시
	for (i = 0; i<numofVertex;  i++) 
	{
		// 정점 v와 정점 i가 연결되었고, 정점 i를 방문하지 않았다면
		if (Vertex_Array[v][i] == 1 && !visited[i])
		{
			// 정점 i에서 다시 DFS를 시작한다
			dfs(i);
		}
	}
}

void add_queue(queue_pointer *front, queue_pointer *rear, int node)
{
   queue_pointer ptr;

   ptr = (queue_pointer)malloc(sizeof(struct queue));
   ptr->vertex = node;
   ptr->link =  NULL;
   if (!*front)
     *front = ptr;
   else
      (*rear)->link = ptr;
   *rear = ptr;
}

int delete_queue(queue_pointer *front)
{
   queue_pointer ptr = *front;
   int vertex = ptr -> vertex;
   *front = ptr->link;;
   free(ptr);
   return vertex;
}

void bfs(int v){
	int i;
	queue_pointer rear, front;
	rear = front = NULL;
	visited[v] = 1;
	printf("%d ", v);
	add_queue(&front, &rear, v);
	while(front){
		v = delete_queue(&front);
		for(i=0; i<numofVertex; i++){   // i를 정점의 번호로 보면 된다.
			// 방문중인 정점(v)과 연결된 인접정점이 있고, 인접정점이 방문되지 않았을때 if 실행
			if(Vertex_Array[v][i] == 1 && !visited[i]){  
				visited[i] = TRUE;  // 방문됨을 1로 보인다
				printf("%d ", i);     // 방문중인 정점 출력
				// 방문중인 정점 i의 값을 queue에 저장하고, 꺼낼땐 i에 대한 인접정점을 찾는다
				add_queue(&front, &rear, i);   
			}
		}
	}
}

