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
	visited[v] = 1; // ���� v�� �湮�ߴٰ� ǥ��
	for (i = 0; i<numofVertex;  i++) 
	{
		// ���� v�� ���� i�� ����Ǿ���, ���� i�� �湮���� �ʾҴٸ�
		if (Vertex_Array[v][i] == 1 && !visited[i])
		{
			// ���� i���� �ٽ� DFS�� �����Ѵ�
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
		for(i=0; i<numofVertex; i++){   // i�� ������ ��ȣ�� ���� �ȴ�.
			// �湮���� ����(v)�� ����� ���������� �ְ�, ���������� �湮���� �ʾ����� if ����
			if(Vertex_Array[v][i] == 1 && !visited[i]){  
				visited[i] = TRUE;  // �湮���� 1�� ���δ�
				printf("%d ", i);     // �湮���� ���� ���
				// �湮���� ���� i�� ���� queue�� �����ϰ�, ������ i�� ���� ���������� ã�´�
				add_queue(&front, &rear, i);   
			}
		}
	}
}

