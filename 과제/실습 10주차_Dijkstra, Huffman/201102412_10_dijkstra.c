#include <stdio.h>
#define INFINITY 999

// dijkstra algorithm ������ ���� �޼ҵ� ����
void dijkstra(int n, int v, int cost[10][10], int dist[]);

void main()
{
	// dijkstra algorithm ������ ���� ���� ����
	int n, v, i, j, cost[10][10], dist[10];

	// �׷����� ��带 �Է¹��� �� ���� n�� ����
	printf("Enter the number of nodes : ");
	scanf("%d", &n);

	// �ݺ����� �̿��ؼ� ��� ���� �Ÿ��� �Է¹��� �� �迭 cost�� ����
	printf("\nEnter the cost matrix : \n");
	
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			scanf("%d", &cost[i][j]);

			// ��� ���� �������� ������ ���� ��, ���Ѵ밪(define�� ��)�� �����Ѵ�.
			if(cost[i][j]==0)
			{
				cost[i][j] = INFINITY;
			}
		}
	}

	/*
	�˰� ���� ����� �ε����� �Է� ���� �� ���� v�� ����
	�迭 �ε����� 0���� �����ϹǷ�, ��� �ÿ��� -1�ؼ� ����Ѵ�.
	���� ���, v�� 3�̶�� �����δ� ��� 2�� ���� ���� ����ϴ� ���̴�.
	����� ���۵� 0���� �����Ѵ�. (���� ���, ��� 0���� ��� 6�̸� 7��)
	*/
	printf("\nEnter the source matrix : ");
	scanf("%d", &v);

	// �ִ� �Ÿ��� ���� �� �迭 dist�� ����
	dijkstra(n, v, cost, dist);

	/*
	�ݺ����� �̿��ؼ� dijkstra �޼ҵ忡�� ����� ��� ���� shortest path�� ���
	(v�� ��� �ڱ� �ڽ��� ����)
	*/
	printf("\nShortest path : \n");

	for(i=1; i<=n; i++)
	{
		if(i!=v)
			printf("%d->%d, cost => %d\n", v-1, i-1, dist[i]);
	}
}

// shortest path�� ���ϱ� ���� �޼ҵ� ����
void dijkstra(int n, int v, int cost[10][10], int dist[])
{
	// shortest path�� ���ϱ� ���� ���� ����
	int i, u, count, w, flag[10], min;

	// �ݺ����� �̿��ؼ� �迭 flag�� ����, dist�� ���� �ʱ�ȭ �����Ѵ�.
	for(i=1; i<=n; i++)
	{
		flag[i] = 0;
		dist[i] = cost[v][i];
	}

	count=2;

	/* 
	����� ������ n�����, �ڱ� �ڽ��� �����ϹǷ� n-1���� ����ϸ� �Ǳ� ������,
	count�� 2�� �����ϰ� ������ �ִ� n������ �ݺ����� �̿��ؼ� shortes path�� ����Ѵ�.
	*/
	while(count<=n)
	{
		min = 99;
		
		// �ݺ����� �迭 flag�� �̿��ؼ� ��� w�� �˻��ߴ� ���� üũ
		for(w=1; w<=n; w++)
		{
			if(dist[w]<min && !flag[w])
			{
				min = dist[w], u = w;
			}
		}

		// üũ������ flag�� 1�� ����
		flag[u] = 1;
		count++;

		/*
		�ݺ����� �̿��ؼ� ����� �Ÿ��� ���� ����� �Ÿ��� ���� ��,
		�迭 dist�� �� ���� ���� ����
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