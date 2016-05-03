#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// �ʱ�ȭ�� ����� �ִ밪 ����
#define MAX 77777

// ��� ���� ������ ���� ����ü ���� �� ����
typedef struct Edge
{
	int src; // ��� ������ ��� ��ȣ
	int dest; // ���� ������ ��� ��ȣ
	int weight; // ������ ����(����ġ)
}Edge;

// bellman_Frod �˰����� �����ϴ� �޼ҵ�
void bellman_Ford(Edge *edge, int edgecount, int nodecount, int startnode);

// bellman_Frod �˰����� �����ϴ� �� �ʿ��� ���� ���� �� �ʱ�ȭ
int *result;
int i = 0;
int j = 0;

void main()
{
	// ������ ���� ����¿� �ʿ��� ���� ���� �� �ʱ�ȭ
	int nodeCount = 0;
	int edgeCount = 0;
	int startNode = 0;

	FILE* fp;
	FILE* fop;

	Edge *edge;
	edge = (Edge*)malloc(sizeof(Edge));
	result = (int*)malloc(sizeof(int));

	// ������ ����� ����
	fp = fopen("week11.txt", "rt");
	fop = fopen("bellman.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");

		return;
	}

	// week11.txt ������ ������ �о ���� nodeCount, startNode, ����ü�迭 edge�� ����
	printf("===== Print the value of text file =====\n");
	fscanf(fp, "%d\n", &nodeCount);
	fscanf(fp, "%d\n", &startNode);

	while(!feof(fp))
	{
		fscanf(fp, "%d %d %d\n", &edge[edgeCount].src, &edge[edgeCount].dest, &edge[edgeCount].weight);

		edgeCount++;
		edge = (Edge*)realloc(edge, sizeof(Edge)*(edgeCount+1));
	}

	// edge�� ������ ���� ��� ���(�׽�Ʈ �뵵)
	for(i=0; i<edgeCount; i++)
	{
		printf("Source : %d, Destination : %d, Weight : %d\n", edge[i].src, edge[i].dest, edge[i].weight);
	}

	// ����� ������ result �迭�� ����� ������ŭ �Ҵ�
	result = (int*)realloc(result, sizeof(int)*nodeCount);

	// bellman_Ford �˰����� ����� ��, ���(result)�� ���
	printf("\n\n===== Print the weight of paths =====\n");
	bellman_Ford(edge, edgeCount, nodeCount, startNode);

	for(i=0; i<nodeCount; i++) 
	{
		printf("%d -> %d ( %d )\n", startNode, i, result[i]);
	}

	// ���� ����� �� ���� �Ҵ� ����
	fclose(fop);
	fclose(fp);

	edge = NULL;
	free(edge);
}

void bellman_Ford(Edge *edge, int edgecount, int nodecount, int start) 
{
	// ����� ������ �迭�� ���� �ʱ�ȭ(����� ��尡 ���� ��� �ڽ��̶�� 0)
	for(i=0; i<nodecount; i++)
	{
		if(i==start)
		{
			result[i] = 0;
		}
		else
		{
			result[i] = MAX;
		}
	}

	// ������ �� ���� ���̿� �����Ƿ� ����� �ݺ����� ������ ����-1�� ����
	for(i=0; i<nodecount-1; i++) 
	{
		for(j=0; j<edgecount; j++) 
		{
			if(result[edge[j].dest] > result[edge[j].src] + edge[j].weight)
			{
				result[edge[j].dest] = result[edge[j].src] + edge[j].weight;
			}
		}
	}

	// ����Ŭ�� �����ϸ� ������� -1�� �����ϰ�, �˰��� ������ ����
	for(i=0; i<edgecount; i++) 
	{
		if(result[edge[i].dest] > result[edge[i].src] + edge[i].weight) 
		{
			printf("ERROR!\n");
			result[i] = -1;
			break;
		}
	}
}