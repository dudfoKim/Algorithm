#include "topological.h"

int main()
{
	int vertex_num;

	printf("총 vertex의 개수를 넣으세요\n");
	scanf("%d", &vertex_num);
	insertEdge();                     // 정점 연결 -> createGraph() 호출
	printGraph(vertex_num);       // Graph 출력
	printf("Topological Sort : \n");   
	topologicalOrder(vertex_num);    // 위상정렬 및 출력

	return 0;
}
