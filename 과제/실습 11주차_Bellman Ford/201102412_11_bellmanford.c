#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 초기화에 사용할 최대값 정의
#define MAX 77777

// 노드 간의 간선에 대한 구조체 선언 및 정의
typedef struct Edge
{
	int src; // 출발 정점의 노드 번호
	int dest; // 도착 정점의 노드 번호
	int weight; // 간선의 길이(가중치)
}Edge;

// bellman_Frod 알고리즘을 수행하는 메소드
void bellman_Ford(Edge *edge, int edgecount, int nodecount, int startnode);

// bellman_Frod 알고리즘을 수행하는 데 필요한 변수 선언 및 초기화
int *result;
int i = 0;
int j = 0;

void main()
{
	// 구현과 파일 입출력에 필요한 변수 선언 및 초기화
	int nodeCount = 0;
	int edgeCount = 0;
	int startNode = 0;

	FILE* fp;
	FILE* fop;

	Edge *edge;
	edge = (Edge*)malloc(sizeof(Edge));
	result = (int*)malloc(sizeof(int));

	// 파일의 입출력 실행
	fp = fopen("week11.txt", "rt");
	fop = fopen("bellman.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");

		return;
	}

	// week11.txt 파일의 내용을 읽어서 각각 nodeCount, startNode, 구조체배열 edge에 저장
	printf("===== Print the value of text file =====\n");
	fscanf(fp, "%d\n", &nodeCount);
	fscanf(fp, "%d\n", &startNode);

	while(!feof(fp))
	{
		fscanf(fp, "%d %d %d\n", &edge[edgeCount].src, &edge[edgeCount].dest, &edge[edgeCount].weight);

		edgeCount++;
		edge = (Edge*)realloc(edge, sizeof(Edge)*(edgeCount+1));
	}

	// edge에 저장한 값을 모두 출력(테스트 용도)
	for(i=0; i<edgeCount; i++)
	{
		printf("Source : %d, Destination : %d, Weight : %d\n", edge[i].src, edge[i].dest, edge[i].weight);
	}

	// 결과를 저장할 result 배열을 노드의 갯수만큼 할당
	result = (int*)realloc(result, sizeof(int)*nodeCount);

	// bellman_Ford 알고리즘을 계산한 후, 결과(result)를 출력
	printf("\n\n===== Print the weight of paths =====\n");
	bellman_Ford(edge, edgeCount, nodeCount, startNode);

	for(i=0; i<nodeCount; i++) 
	{
		printf("%d -> %d ( %d )\n", startNode, i, result[i]);
	}

	// 파일 입출력 및 동적 할당 해제
	fclose(fop);
	fclose(fp);

	edge = NULL;
	free(edge);
}

void bellman_Ford(Edge *edge, int edgecount, int nodecount, int start) 
{
	// 결과를 저장할 배열의 값을 초기화(계산할 노드가 시작 노드 자신이라면 0)
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

	// 간선은 각 정점 사이에 있으므로 계산할 반복문을 정점의 갯수-1번 실행
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

	// 사이클이 존재하면 결과값을 -1로 설정하고, 알고리즘 수행을 중지
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