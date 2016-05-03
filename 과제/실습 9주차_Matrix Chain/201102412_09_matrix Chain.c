// 구현을 위한 헤더파일과 상수 선언
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 구현을 위한 메소드 선언
void duplicate_Array(int *p);
void matrix_Chain(int *p, int n);
void print_Optimal(int **s, int i, int j);

// 구현을 위한 변수 선언
int **m;
int **s;
int *p;
int *resultP;
int pCount = 0;
int num = 1;
FILE* fop;

void main()
{
	// 파일 입출력과 배열을 위한 변수 선언 및 초기화
	FILE* fp;
	int i = 0;
	int j = 0;
	int mSize = 0;
	int pSize = 0;

	p = (int*)malloc(sizeof(int));
	m = (int**)malloc(sizeof(int*));
	s = (int**)malloc(sizeof(int*));

	// 텍스트 파일 내용을 읽어들일 파일 이름 지정
	fp = fopen("data09.txt", "rt");
	fop = fopen("output_matrix .txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");
	
		return;
	}

	// 텍스트 파일에 있는 괄호의 순서쌍 값을 읽어온다.
	printf("===== Print the value of text file =====\n");

	while(!feof(fp))
	{
		pCount = pCount+2;
		p = (int*)realloc(p, sizeof(int)*(pCount));
	
		fscanf(fp, "(%d,%d)", &(p[pCount-2]), &(p[pCount-1]));
	}
	
	pCount = pCount-2;

	// 읽어온 값들을 모두 출력한다.
	printf("Original Matrix : ");

	for(i=0; i<pCount; i++)
	{
		printf("%d ", p[i]);
	}

	// 읽어온 값의 중복을 제거한 후, p값에 대한 배열을 만든다.
	mSize = (pCount/2);
	pSize = mSize+1;
	duplicate_Array(p, pSize);

	// 중복을 제거한 p배열을 출력한다.
	printf("\n\nValue of p : ");

	for(i=0; i<pSize; i++)
	{
		printf("%d ", resultP[i]);
	}

	printf("\n");

	// dynamic programming을 위한 2차원 배열 2개를 만든다.
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

	// 값을 모두 0으로 초기화
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

	// matrix Chain을 실행한 후 결과를 출력한다.
	matrix_Chain(resultP, pSize);
	print_Optimal(s, 1, pSize-1);

	// 동적 할당을 해제하고, 파일 입출력을 끝내면서 프로그램 종료
	fclose(fp);
	fclose(fop);

	m = NULL;
	free(m);

	p = NULL;
	free(p);
}

// 읽어온 값들의 중복을 제거한 후 p배열에 저장한다.
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

// n x n 배열을 이용해서 matrix Chain을 구한다.
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

// 재귀함수로 배열의 결합 순서를 정해서 출력한다.
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