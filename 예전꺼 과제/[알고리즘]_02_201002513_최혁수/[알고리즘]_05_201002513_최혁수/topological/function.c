#include "topological.h"
/* Graph 초기화 */
void initGraph(int Vertex){
	int i;
	for(i=0; i<Vertex; i++){
		graph[i].count = 0;
		graph[i].link = NULL;
	}
}
/* 정점 연결 및 createGraph() 호출 */
void insertEdge(){
	int vertex1, vertex2;
	printf("startVertex, endVertex를 입력하세요(종료 : 0 -1) : \n");
	while(1){
		scanf("%d %d",&vertex1, &vertex2);
		if(vertex1 == 0 && vertex2 == -1) break;  // 종료
		createGraph(vertex1, vertex2);  // 그래프 생성
	}
	printf("\n");
}

void createGraph(int vertex1, int vertex2){
	node_pointer temp;  // 데이터(vertex2)를 갖는 노드 생성
	node_pointer gogo; // 탐색을 위한 노드

	temp = (node_pointer)malloc(sizeof(node));
	temp->vertex = vertex2;  
	temp->link = NULL;

	gogo = graph[vertex1].link;    // gogo 노드 초기화
	if(graph[vertex1].link == NULL){  // graph[]에 딸린 노드가 없을때
		graph[vertex1].link = temp;   // vertex2 노드를 연결
	}
	else{		
		while(gogo->link!=NULL){	   // 노드가 연결되있을때
			gogo = gogo->link;	   // 노드의 끝을 탐색
		}
		gogo->link = temp;           // 노드의 끝에 연결
	}
	graph[vertex2].count++;          // indegree 값 +1
}
/* 위상정렬 및 출력 */
void topologicalOrder(int vertex){
	node_pointer temp;      // 탐색 노드
	int top=-1;                 // stack 의 기능 구현
	int i;                        

	for(i=0; i<vertex; i++){ 
		if(graph[i].count == 0){
			graph[i].count = top;  // 초기 index=0 에 대한 설정
			top = i;                  // top의 값 재정의
		}
	}
	while(top!=-1){                  // 위상정렬이 끝날때
		printf("%d  ", top);          // top의 값 출력 
		for(temp=graph[top].link; temp!=NULL; temp=temp->link)
			 // 인접노드의 데이터(vertex)를 graph[]의 index에 접목하여 indegree값을 1 감소
			graph[temp->vertex].count--;   
		top=graph[top].count;     // top 재정의

		/* 앞서 graph[]의 indegree의 재정의값중, 0이 발생할 경우를 탐색 */
		/* 즉, indegree=0이 발생할 경우, top에 해당 graph index값을 top에 재정의 */
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
			printf("->%d", temp->vertex);  // graph[]의 연결노드 데이터(vertex)정보를 출력
		}
		printf("\n");
	}
	printf("\n");
}