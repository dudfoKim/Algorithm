#include "DFSBFS_list.h"
/* headNodes & visited �����Ҵ� �� �ʱ�ȭ */
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
/* visited �ʱ�ȭ */
void vertexInit(){
	int i;
		for(i=0; i<numofVertex; i++) visited[i] = 0;
}
/* v1, v2 ������ v1->v2�� ���� */
void insertEdge(int v1, int v2){
	pnode new_node=NULL;
	pnode find=NULL;
	new_node = (pnode)malloc(sizeof(pnode));   // node ���� �� vertex, link ���� ����
	new_node->vertex = v2;
	new_node->link = NULL;

	find = headNodes[v1];
	if(find==NULL){    // ���� v1�� ����� ������ ������
		headNodes[v1] = new_node;  
		return ;
	}
	while(find->link!=NULL){    // �������� ����� ���� ã��
		find = find->link;
	}
	find->link = new_node;
}
/* ���� ���� */
void deleteVertex(int Vertex){        // Vertex = �����ϰ��� �ϴ� ����
	pnode prev;
	pnode temp;
	int i=0;
	headNodes[Vertex] = NULL;    // Vertex�� ���� ���۵� ���������� ������ ���´�
	for(; i<numofVertex; i++){       // �̿��� headNodes �� ����� Vertex�� ã�� ����
		prev = NULL;
		temp = NULL;
		temp=headNodes[i];
		while(temp!=NULL){
			if(temp->vertex == Vertex){
				// if) Vertex:0, 1->0->2 �ϰ��, 1->2�� ��ȯ �Ǵ� 1->0 �� ���, 1->NULL 
				if(temp==headNodes[i]) headNodes[i] = headNodes[i]->link;  
				else prev->link = temp->link;  // if) Vertex:0 1->2->3->0->4 �ϰ��, 1->2->3->4�� ��ȯ
			}
			if(temp->link == NULL) break;  // Vertex�� ����Ǿ����� ������, break;
			prev = temp; 
			temp = temp->link;               // ����ؼ� �������� ����
		}
	}
}
/* ������带 �湮�ϸ鼭 ��� */
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
/* DFS ���� */
void dfs(int v){	
	pnode w;
	visited[v]=TRUE;   // �湮�� �ش� �������� 1�� ��ȯ
	printf("%d ",v);
	for(w=headNodes[v]; w; w=w->link){   // v:0, 0�� �������� ������� �湮 ����
		if(!visited[w->vertex]){   // �湮���� ���� ������ �������, ����� ����(w->vertex)
			dfs(w->vertex);
		}
	}
}
/* queue�� �����Ҵ� �޾� link�� �����ϸ鼭 data������ BFS�� �̹湮 ������ ���� */
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
/* FIFO�� ���� queue�� ����� ���� �ϳ��� return & free */
int delete_queue(queue_pointer *front)
{
   queue_pointer ptr = *front;
   int vertex = ptr -> vertex;
   *front = ptr->link;;
   free(ptr);
   return vertex;
}
/* DFS ���� */
void bfs(int v)
{
   pnode w;
   queue_pointer front,rear;
   front = rear = NULL; 
   visited[v] = TRUE;
   printf("%d ",v);
   add_queue(&front, &rear, v);  // �湮������ ��� queue�� ����
   while (front) {  // �̹湮 ������ ���������� ����
      v = delete_queue(&front);   // FIFO�� ���� ���� v�� ����
	  for (w = headNodes[v]; w; w=w->link)
	  if (!visited[w->vertex]) {       // �湮���� ���� �����϶�
		  visited[w->vertex] = TRUE;
		  printf("%d ", w->vertex);
	      add_queue(&front,&rear,w->vertex);     // �湮������ queue�� ����
	  }
   }
}
