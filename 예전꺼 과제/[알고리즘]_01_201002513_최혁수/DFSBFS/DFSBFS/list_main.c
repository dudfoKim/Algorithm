#include "DFSBFS_list.h"
int main()
{
	int flag, vertex1, vertex2, del_vertex;
	createGraph(8);
	do{
		printf("1.Insert  2.Delete  3.Print  4.DFS  5.BFS  6.Quit\n");
		scanf("%d",&flag);
		switch(flag){
		case 1:
			printf("Start Vertex와 End Vertex를 입력하세요 (quit:-1 -1)\n");
			scanf("%d%d",&vertex1,&vertex2);
			while(vertex1!=-1){
				insertEdge(vertex1, vertex2);
				insertEdge(vertex2, vertex1);
				printf("Start Vertex와 End Vertex를 입력하세요 (quit:-1 -1)\n");
				scanf("%d%d",&vertex1,&vertex2);
			}
			break;
		case 2:
			printf("삭제할 Vertex를 입력하세요 : ");
			scanf("%d",&del_vertex);
			deleteVertex(del_vertex);
			break;
		case 3:
			printGraph();
			break;
		case 4:
			vertexInit();
			dfs(0);
			printf("\n");
			break;
		case 5:
			vertexInit();
			bfs(0);
			printf("\n");
			break;
		}
	}while(flag!=6);
	return 0;
}
