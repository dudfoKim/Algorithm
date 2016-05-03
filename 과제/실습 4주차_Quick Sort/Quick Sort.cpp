// �ҽ� �ڵ� ������ ���� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// �� ���� ������ ���� �Լ� ����random_partition
void quickSort(int *array, int p, int q);
int partition(int *array, int p, int q);
void random_quickSort(int *array, int p, int q);
int random_partition(int *array, int p, int q);
void swap(int *a, int *b);
void checkArray(int *array, int n);

void main( )
{
	// ���� ����°� �ݺ����� ���� ����
    FILE* fp;
	FILE* fop;
	int i = 0;
	int j = 0;

	// �ؽ�Ʈ ������ �о���� ���� ����.
	int *valueArray;
	int count = 1;

	// �ð� ������ ���� ����
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);

	valueArray = (int*)malloc(sizeof(int));

	fp = fopen("data04.txt", "rt");
	fop = fopen("00_201102412_quickSort.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");

		return;
	}

	// �ؽ�Ʈ ���Ͽ� ������ ���� ������ �о�� �� ������ ������ �迭�� ����
	while(!feof(fp))
	{
		valueArray = (int*)realloc(valueArray, sizeof(int)*count);

		fscanf(fp, "%d,", &(valueArray[count-1]));
		count++;
	}

	count--;

	printf("Quick sorting...\n");
	checkArray(valueArray, count);

	QueryPerformanceCounter(&start);
	random_quickSort(valueArray, 0, count-1);
	//quickSort(valueArray, 0, count-1);
	QueryPerformanceCounter(&end);

	printf("\nSorting success!\n");

	checkArray(valueArray, count);
	printf("\n\nRequired %.10f seconds\n", (float)(end.QuadPart-start.QuadPart)/freq.QuadPart);

	printf("\nThen, let's print at document!\n");

	for(i=0; i<count; i++)
	{
		fprintf(fop, "%d,", valueArray[i]);
	}

	printf("\n");

	fclose(fp);

	valueArray = NULL;
	free(valueArray);

	// ���� �Ҵ��� �����ϰ�, ���� ������� �����鼭 ���α׷� ����
}

// �� ������ �����ϴ� �޼ҵ�
void quickSort(int *array, int p, int q)
{
	if(p<q)
	{
		int pivot = partition(array, p, q);
		quickSort(array, p , pivot-1);
		quickSort(array, pivot+1, q);
	}
}

void random_quickSort(int *array, int p, int q)
{
	if(p<q)
	{
		int pivot = random_partition(array, p, q);
		quickSort(array, p , pivot-1);
		quickSort(array, pivot+1, q);
	}
}

// ������ ���Ҹ� �̵���Ű�鼭 �� ������ ó�����ִ� �޼ҵ�
int partition(int *array, int p, int q)
{
	int x = array[q];
	int i = p-1;
	int j = 0;

	for(j=p; j<=q-1; j++)
	{
		if(array[j]<=x)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}

	i++;

	swap(&array[i], &array[q]);

	return i;
}

// �迭�� ����ȭ�� ���� ������ ���Ҹ� ó���ϴ� �޼ҵ�
int random_partition(int *array, int p, int q)
{
	int iPivot;
	int ptrCenter = (p+q)/2;

	if(!(array[p]<array[ptrCenter]^array[ptrCenter]<array[q]))
	{
		iPivot = ptrCenter;
	}
	else if(!(array[ptrCenter]<array[p]^array[p]<array[q]))
	{
		iPivot = p;
	}
	else
	{
		iPivot = q;
	}

	swap(&array[iPivot], &array[q]);

	return partition(array, p, q);
}

// �� ���� �ٲ��ִ� �޼ҵ�
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// ��� ����� ���� �׽�Ʈ �޼ҵ�
void checkArray(int *array, int n)
{
	int i = 0;
	int index = n/100;

	for(i=0; i<index; i++)
	{
		if(i==i*10)
		{
			printf("%\n");
		}

		printf("%d ", array[i]);
	}
}