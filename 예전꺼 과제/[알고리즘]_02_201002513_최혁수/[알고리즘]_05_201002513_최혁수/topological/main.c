#include "topological.h"

int main()
{
	int vertex_num;

	printf("�� vertex�� ������ ��������\n");
	scanf("%d", &vertex_num);
	insertEdge();                     // ���� ���� -> createGraph() ȣ��
	printGraph(vertex_num);       // Graph ���
	printf("Topological Sort : \n");   
	topologicalOrder(vertex_num);    // �������� �� ���

	return 0;
}
