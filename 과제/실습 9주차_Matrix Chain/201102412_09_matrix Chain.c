// ������ ���� ������ϰ� ��� ����
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// ������ ���� �޼ҵ� ����
void duplicate_Array(int *p);
void matrix_Chain(int *p, int n);
void print_Optimal(int **s, int i, int j);

// ������ ���� ���� ����
int **m;
int **s;
int *p;
int *resultP;
int pCount = 0;
int num = 1;
FILE* fop;

void main()
{
	// ���� ����°� �迭�� ���� ���� ���� �� �ʱ�ȭ
	FILE* fp;
	int i = 0;
	int j = 0;
	int mSize = 0;
	int pSize = 0;

	p = (int*)malloc(sizeof(int));
	m = (int**)malloc(sizeof(int*));
	s = (int**)malloc(sizeof(int*));

	// �ؽ�Ʈ ���� ������ �о���� ���� �̸� ����
	fp = fopen("data09.txt", "rt");
	fop = fopen("output_matrix .txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");
	
		return;
	}

	// �ؽ�Ʈ ���Ͽ� �ִ� ��ȣ�� ������ ���� �о�´�.
	printf("===== Print the value of text file =====\n");

	while(!feof(fp))
	{
		pCount = pCount+2;
		p = (int*)realloc(p, sizeof(int)*(pCount));
	
		fscanf(fp, "(%d,%d)", &(p[pCount-2]), &(p[pCount-1]));
	}
	
	pCount = pCount-2;

	// �о�� ������ ��� ����Ѵ�.
	printf("Original Matrix : ");

	for(i=0; i<pCount; i++)
	{
		printf("%d ", p[i]);
	}

	// �о�� ���� �ߺ��� ������ ��, p���� ���� �迭�� �����.
	mSize = (pCount/2);
	pSize = mSize+1;
	duplicate_Array(p, pSize);

	// �ߺ��� ������ p�迭�� ����Ѵ�.
	printf("\n\nValue of p : ");

	for(i=0; i<pSize; i++)
	{
		printf("%d ", resultP[i]);
	}

	printf("\n");

	// dynamic programming�� ���� 2���� �迭 2���� �����.
	m = (int**)realloc(m, sizeof(int)*(pSize));

	for(i=0; i<pSize; i++)
	{
		m[i] = (int*)malloc(sizeof(int)*pSize);
	}

	s = (int**)realloc(s, sizeof(int)*(pSize));

	for(i=0; i<pSize; i++)
	{
		s[i] = (int*)malloc(sizeof(int)*pSize);
	}

	// ���� ��� 0���� �ʱ�ȭ
	for(i=0; i<pSize; i++)
	{
		for(j=0; j<pSize; j++)
		{
			m[i][j] = 0;
		}
	}

	for(i=0; i<pSize; i++)
	{
		for(j=0; j<pSize; j++)
		{
			s[i][j] = 0;
		}
	}

	// matrix Chain�� ������ �� ����� ����Ѵ�.
	matrix_Chain(resultP, pSize);
	print_Optimal(s, 1, pSize-1);

	// ���� �Ҵ��� �����ϰ�, ���� ������� �����鼭 ���α׷� ����
	fclose(fp);
	fclose(fop);

	m = NULL;
	free(m);

	p = NULL;
	free(p);
}

// �о�� ������ �ߺ��� ������ �� p�迭�� �����Ѵ�.
void duplicate_Array(int *p, int size)
{
	int i = 0;
	int j = 0;

	resultP = (int*)malloc(sizeof(int)*size);

	for(i=0; i<pCount; i++)
	{
		if(p[i]!=p[i+1])
		{
			resultP[j] = p[i];
			j++;
		}
	}
}

// n x n �迭�� �̿��ؼ� matrix Chain�� ���Ѵ�.
void matrix_Chain(int *p, int n)
{
	int i = 0;
	int l = 0;
	int j = 0;
	int k = 0;
	int q = 0;
	
	for(i=1; i<n; i++)
	{
		m[i][i] = 0;
	}

	for(l=2; l<n; l++)
	{
		for(i=1; i<=n-l; i++)
		{
			j= i+l-1;
			m[i][j] = 77777;

			for(k=i; k<=j-1; k++)
			{
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

				if(q<m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	printf("\nPrint the Value of Matrix-Chain : \n");

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%d ", m[i][j]);
		}

		printf("\n");
	}

	printf("\n\nFinal Min Cost : %d\n", m[1][n-1]);
}

// ����Լ��� �迭�� ���� ������ ���ؼ� ����Ѵ�.
void print_Optimal(int **s, int i, int j)
{
	if(i==j)
	{
		fprintf(fop, "A %d ", i++);
		printf(" A %d ", num++);
	}
	else
	{
		fprintf(fop, " ( ");
		printf(" ( ");
		print_Optimal(s, i, s[i][j]);
		print_Optimal(s, s[i][j]+1, j);
		printf(" ) ");
		fprintf(fop, " ) ");
	}
}