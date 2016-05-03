#include "DFSBFS_list.h"
/* headNodes & visited 동적할당 및 초기화 */
void createGraph(int numVertex){
	int i=0;
		numofVertex = numVertex;
		headNodes = (pnode*)malloc(sizeof(pnode)*numVertex);
		while(i<numVertex){
			headNodes[i++]=NULL;
		}
		visited = (int*)malloc(sizeof(int)*numofVertex);
		for(i=0; i<numofVertex; i++) visited[i] = 0;
}
/* visited 초기화 */
void vertexInit(){
	int i;
		for(i=0; i<numofVertex; i++) visited[i] = 0;
}
/* v1, v2 정점을 v1->v2로 연결 */
void insertEdge(int v1, int v2){
	pnode new_node=NULL;
	pnode find=NULL;
	new_node = (pnode)malloc(sizeof(pnode));   // node 선언 및 vertex, link 정보 저장
	new_node->vertex = v2;
	new_node->link = NULL;

	find = headNodes[v1];
	if(find==NULL){    // 정점 v1에 연결된 정점이 없을때
		headNodes[v1] = new_node;  
		return ;
	}
	while(find->link!=NULL){    // 마지막에 연결된 정점 찾기
		find = find->link;
	}
	find->link = new_node;
}
/* 정점 삭제 */
void deleteVertex(int Vertex){        // Vertex = 삭제하고자 하는 정점
	pnode prev;
	pnode temp;
	int i=0;
	headNodes[Vertex] = NULL;    // Vertex로 부터 시작된 인접정점의 연결을 끊는다
	for(; i<numofVertex; i++){       // 이외의 headNodes 에 연결된 Vertex를 찾아 삭제
		prev = NULL;
		temp = NULL;
		temp=headNodes[i];
		while(temp!=NULL){
			if(temp->vertex == Vertex){
				// if) Vertex:0, 1->0->2 일경우, 1->2로 변환 또는 1->0 일 경우, 1->NULL 
				if(temp==headNodes[i]) headNodes[i] = headNodes[i]->link;  
				else prev->link = temp->link;  // if) Vertex:0 1->2->3->0->4 일경우, 1->2->3->4로 변환
			}
			if(temp->link == NULL) break;  // Vertex가 연결되어있지 않을때, break;
			prev = temp; 
			temp = temp->link;               // 계속해서 인접노드로 연결
		}
	}
}
/* 인접노드를 방문하면서 출력 */
void printGraph()
{
	pnode first;
	int i=0;
	for(i=0; i<numofVertex; i++)
	{
		if(headNodes[i]!=NULL){
		first = headNodes[i];
		printf("%d",i);
		while(first->link != NULL){
			printf(" -> %d", first->vertex);
			first = first->link;
		}
		printf(" -> %d\n", first->vertex);
		}
	}
}
/* DFS 구현 */
void dfs(int v){	
	pnode w;
	visited[v]=TRUE;   // 방문시 해당 정점값을 1로 변환
	printf("%d ",v);
	for(w=headNodes[v]; w; w=w->link){   // v:0, 0을 시작으로 인접노드 방문 실행
		if(!visited[w->vertex]){   // 방문하지 않은 정점이 있을경우, 재귀적 실행(w->vertex)
			dfs(w->vertex);
		}
	}
}
/* queue를 동적할당 받아 link로 연결하면서 data값으로 BFS의 미방문 정점을 저장 */
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
/* FIFO에 의해 queue에 저장된 값을 하나씩 return & free */
int delete_queue(queue_pointer *front)
{
   queue_pointer ptr = *front;
   int vertex = ptr -> vertex;
   *front = ptr->link;;
   free(ptr);
   return vertex;
}
/* DFS 구현 */
void bfs(int v)
{
   pnode w;
   queue_pointer front,rear;
   front = rear = NULL; 
   visited[v] = TRUE;
   printf("%d ",v);
   add_queue(&front, &rear, v);  // 방문정점을 모두 queue에 저장
   while (front) {  // 미방문 정점이 없을때까지 실행
      v = delete_queue(&front);   // FIFO에 의한 값을 v에 저장
	  for (w = headNodes[v]; w; w=w->link)
	  if (!visited[w->vertex]) {       // 방문하지 않은 정점일때
		  visited[w->vertex] = TRUE;
		  printf("%d ", w->vertex);
	      add_queue(&front,&rear,w->vertex);     // 방문정점을 queue에 저장
	  }
   }
}
