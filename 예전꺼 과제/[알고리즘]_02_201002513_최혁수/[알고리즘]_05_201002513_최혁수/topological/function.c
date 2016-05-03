#include "topological.h"
/* Graph �ʱ�ȭ */
void initGraph(int Vertex){
	int i;
	for(i=0; i<Vertex; i++){
		graph[i].count = 0;
		graph[i].link = NULL;
	}
}
/* ���� ���� �� createGraph() ȣ�� */
void insertEdge(){
	int vertex1, vertex2;
	printf("startVertex, endVertex�� �Է��ϼ���(���� : 0 -1) : \n");
	while(1){
		scanf("%d %d",&vertex1, &vertex2);
		if(vertex1 == 0 && vertex2 == -1) break;  // ����
		createGraph(vertex1, vertex2);  // �׷��� ����
	}
	printf("\n");
}

void createGraph(int vertex1, int vertex2){
	node_pointer temp;  // ������(vertex2)�� ���� ��� ����
	node_pointer gogo; // Ž���� ���� ���

	temp = (node_pointer)malloc(sizeof(node));
	temp->vertex = vertex2;  
	temp->link = NULL;

	gogo = graph[vertex1].link;    // gogo ��� �ʱ�ȭ
	if(graph[vertex1].link == NULL){  // graph[]�� ���� ��尡 ������
		graph[vertex1].link = temp;   // vertex2 ��带 ����
	}
	else{		
		while(gogo->link!=NULL){	   // ��尡 �����������
			gogo = gogo->link;	   // ����� ���� Ž��
		}
		gogo->link = temp;           // ����� ���� ����
	}
	graph[vertex2].count++;          // indegree �� +1
}
/* �������� �� ��� */
void topologicalOrder(int vertex){
	node_pointer temp;      // Ž�� ���
	int top=-1;                 // stack �� ��� ����
	int i;                        

	for(i=0; i<vertex; i++){ 
		if(graph[i].count == 0){
			graph[i].count = top;  // �ʱ� index=0 �� ���� ����
			top = i;                  // top�� �� ������
		}
	}
	while(top!=-1){                  // ���������� ������
		printf("%d  ", top);          // top�� �� ��� 
		for(temp=graph[top].link; temp!=NULL; temp=temp->link)
			 // ��������� ������(vertex)�� graph[]�� index�� �����Ͽ� indegree���� 1 ����
			graph[temp->vertex].count--;   
		top=graph[top].count;     // top ������

		/* �ռ� graph[]�� indegree�� �����ǰ���, 0�� �߻��� ��츦 Ž�� */
		/* ��, indegree=0�� �߻��� ���, top�� �ش� graph index���� top�� ������ */
		for(i=0; i<vertex; i++)     
			if(graph[i].count==0){
				graph[i].count=top;
				top=i;
			}
	}
	printf("\n");
}

void printGraph(int vertex){

	node_pointer temp;
	int i;

	for(i=0; i<vertex; i++){
		printf("[%d : <%d>]", i, graph[i].count);
		for(temp=graph[i].link; temp!=NULL; temp=temp->link)
		{
			printf("->%d", temp->vertex);  // graph[]�� ������ ������(vertex)������ ���
		}
		printf("\n");
	}
	printf("\n");
}