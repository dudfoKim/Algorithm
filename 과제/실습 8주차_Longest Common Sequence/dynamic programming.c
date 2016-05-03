// 구현을 위한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 구현을 위한 메소드 선언
void print_LCS(int **c, char **x, int i, int j);

// 구현을 위한 변수 선언(결과값 출력)
char *result;
int count = 0;

void main()
{
	// 파일 입출력과 배열을 위한 변수 선언 및 초기화
	FILE* fp;
	int i = 0;
	int j = 0;
	int count1 = 0;
	int count2 = 0;
	int **num;
	int length = 0;
	char *value1;
	char *value2;

	value1 = (char*)malloc(sizeof(char));
	value2 = (char*)malloc(sizeof(char));
	num = (int**)malloc(sizeof(int*));
	result = (char*)malloc(sizeof(char));

	// 텍스트 파일 내용을 읽어들일 파일 이름 지정
	fp = fopen("data08_1.txt", "rt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");
	
		return;
	}

	// 텍스트파일로 읽어온 값들을 배열 두개로 나눠서 출력(정상작동하는 지 테스트 용)
	printf("===== Print the value of text file =====\n");
	printf("Array1 : ");

	while(1)
	{
		value1 = (char*)realloc(value1, sizeof(char)*(++count1));
		value1[count1-1] = fgetc(fp);

		if(value1[count1-1]==10)
		{
			break;
		}

		printf("%c", value1[count1-1]);
	}

	value1[--count1] = NULL;

	printf("\nArray2 : ");

	while(1)
	{
		value2 = (char*)realloc(value2, sizeof(char)*(++count2));
		value2[count2-1] = fgetc(fp);

		if(value2[count2-1]==-1)
		{
			break;
		}

		printf("%c", value2[count2-1]);
	}

	value2[--count2] = NULL;

	// 읽어온 텍스트의 길이+1 만큼 2차원 배열을 할당
	count1++;
	count2++;
	num = (int**)realloc(num, sizeof(int)*(count2));

	for(i=0; i<count2; i++)
	{
		num[i] = (int*)malloc(sizeof(int)*count1);
	}

	// 값을 모두 0으로 초기화
	for(i=0; i<count2; i++)
	{
		for(j=0; j<count1; j++)
		{
			num[i][j] = 0;
		}
	}

	// dynamic programming 방법으로 2차원 배열에 값을 할당
	for(i=1; i<count2; i++)
	{
		for(j=1; j<count1; j++)
		{
			if(value1[j-1]==value2[i-1])
			{
				num[i][j] = num[i-1][j-1] + 1;
			}
			else if(num[i-1][j]>=num[i][j-1])
			{
				num[i][j] = num[i-1][j];
			}
			else
			{
				num[i][j] = num[i][j-1];
			}
		}
	}

	/*
	// 테스트 용 출력
	printf("\n\n");

	for(i=0; i<count2; i++)
	{
		for(j=0; j<count1; j++)
		{
			printf("%d ", num[i][j]);
		}

		printf("\n");
	}
	*/

	printf("\nLCS : ");
 	print_LCS(num, &value1, count1-1, count2-1);

	// LCS의 최종 결과값 출력
	for(i=0; i<count; i++)
	{
		printf("%c ", result[count-i-1]);
	}

	printf("\n\n===== LCS finish! =====\n");

	// 동적 할당을 해제하고, 파일 입출력을 끝내면서 프로그램 종료
	fclose(fp);

	result = NULL;
	free(result);

	value1 = NULL;
	free(value1);

	value2 = NULL;
	free(value2);
}

/* 
메인함수에서 할당한 2차원 배열에 따라 공통된 문자를
result 배열에 char 형태로 저장한다.(재귀구조)
역순으로 출력되므로, 이렇게 별도의 배열을 이용해 출력하면
차례대로 확인할 수 있다.
*/
void print_LCS(int **c, char **x, int i, int j)
{
	if(i==0 || j==0)
	{
		return;
	}
	if((c[j][i])-1==c[j-1][i-1] && (c[j][i])-1==c[j][i-1] && (c[j][i])-1==c[j-1][i])
	{
		result = (char*)realloc(result, sizeof(char)*(++count));
		result[count-1] =  (*x)[i-1];
		print_LCS(c, x, i-1, j-1);
	}
	else if(c[j][i]==c[j][i-1])
	{
		print_LCS(c, x, i-1, j);
	}
	else
	{
		print_LCS(c, x, i, j-1);
	}
}
