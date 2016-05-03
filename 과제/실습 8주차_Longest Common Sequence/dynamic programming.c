// ������ ���� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// ������ ���� �޼ҵ� ����
void print_LCS(int **c, char **x, int i, int j);

// ������ ���� ���� ����(����� ���)
char *result;
int count = 0;

void main()
{
	// ���� ����°� �迭�� ���� ���� ���� �� �ʱ�ȭ
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

	// �ؽ�Ʈ ���� ������ �о���� ���� �̸� ����
	fp = fopen("data08_1.txt", "rt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");
	
		return;
	}

	// �ؽ�Ʈ���Ϸ� �о�� ������ �迭 �ΰ��� ������ ���(�����۵��ϴ� �� �׽�Ʈ ��)
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

	// �о�� �ؽ�Ʈ�� ����+1 ��ŭ 2���� �迭�� �Ҵ�
	count1++;
	count2++;
	num = (int**)realloc(num, sizeof(int)*(count2));

	for(i=0; i<count2; i++)
	{
		num[i] = (int*)malloc(sizeof(int)*count1);
	}

	// ���� ��� 0���� �ʱ�ȭ
	for(i=0; i<count2; i++)
	{
		for(j=0; j<count1; j++)
		{
			num[i][j] = 0;
		}
	}

	// dynamic programming ������� 2���� �迭�� ���� �Ҵ�
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
	// �׽�Ʈ �� ���
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

	// LCS�� ���� ����� ���
	for(i=0; i<count; i++)
	{
		printf("%c ", result[count-i-1]);
	}

	printf("\n\n===== LCS finish! =====\n");

	// ���� �Ҵ��� �����ϰ�, ���� ������� �����鼭 ���α׷� ����
	fclose(fp);

	result = NULL;
	free(result);

	value1 = NULL;
	free(value1);

	value2 = NULL;
	free(value2);
}

/* 
�����Լ����� �Ҵ��� 2���� �迭�� ���� ����� ���ڸ�
result �迭�� char ���·� �����Ѵ�.(��ͱ���)
�������� ��µǹǷ�, �̷��� ������ �迭�� �̿��� ����ϸ�
���ʴ�� Ȯ���� �� �ִ�.
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
