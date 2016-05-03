#include <stdio.h>
#define INFINITY 999

// dijkstra algorithm 구현을 위한 메소드 선언
void dijkstra(int n, int v, int cost[10][10], int dist[]);

void main()
{
	// dijkstra algorithm 구현을 위한 변수 선언
	int n, v, i, j, cost[10][10], dist[10];

	// 그래프의 노드를 입력받은 후 변수 n에 저장
	printf("Enter the number of nodes : ");
	scanf("%d", &n);

	// 반복문을 이용해서 노드 간의 거리를 입력받은 후 배열 cost에 저장
	printf("\nEnter the cost matrix : \n");
	
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			scanf("%d", &cost[i][j]);

			// 노드 간의 직접적인 간선이 없을 때, 무한대값(define한 값)을 저장한다.
			if(cost[i][j]==0)
			{
				cost[i][j] = INFINITY;
			}
		}
	}

	/*
	알고 싶은 노드의 인덱스를 입력 받은 후 변수 v에 저장
	배열 인덱스는 0부터 시작하므로, 출력 시에는 -1해서 출력한다.
	예를 들어, v가 3이라면 실제로는 노드 2에 대한 값을 출력하는 것이다.
	노드의 시작도 0부터 시작한다. (예를 들엇, 노드 0부터 노드 6이면 7개)
	*/
	printf("\nEnter the source matrix : ");
	scanf("%d", &v);

	// 최단 거리를 구한 후 배열 dist에 저장
	dijkstra(n, v, cost, dist);

	/*
	반복문을 이용해서 dijkstra 메소드에서 계산한 노드 간의 shortest path를 출력
	(v인 노드 자기 자신은 제외)
	*/
	printf("\nShortest path : \n");

	for(i=1; i<=n; i++)
	{
		if(i!=v)
			printf("%d->%d, cost => %d\n", v-1, i-1, dist[i]);
	}
}

// shortest path를 구하기 위한 메소드 정의
void dijkstra(int n, int v, int cost[10][10], int dist[])
{
	// shortest path를 구하기 위한 변수 선언
	int i, u, count, w, flag[10], min;

	// 반복문을 이용해서 배열 flag의 값과, dist의 값을 초기화 선언한다.
	for(i=1; i<=n; i++)
	{
		flag[i] = 0;
		dist[i] = cost[v][i];
	}

	count=2;

	/* 
	노드의 갯수가 n개라면, 자기 자신은 제외하므로 n-1번만 계산하면 되기 때문에,
	count를 2로 선언하고 범위가 최대 n까지인 반복문을 이용해서 shortes path를 계산한다.
	*/
	while(count<=n)
	{
		min = 99;
		
		// 반복문과 배열 flag를 이용해서 노드 w를 검사했는 지를 체크
		for(w=1; w<=n; w++)
		{
			if(dist[w]<min && !flag[w])
			{
				min = dist[w], u = w;
			}
		}

		// 체크했으면 flag를 1로 설정
		flag[u] = 1;
		count++;

		/*
		반복문을 이용해서 저장된 거리와 새로 계산한 거리를 비교한 후,
		배열 dist에 더 작은 값을 저장
		*/
		for(w=1; w<=n; w++)
		{
			if((dist[u]+cost[u][w]<dist[w]) && !flag[w])
			{
				dist[w] = dist[u] + cost[u][w];
			}
		}
	}
}