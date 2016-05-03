// 소스 코드 구현을 위한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 퀵 정렬 구현을 위한 함수 선언random_partition
void quickSort(int *array, int p, int q);
int partition(int *array, int p, int q);
void random_quickSort(int *array, int p, int q);
int random_partition(int *array, int p, int q);
void swap(int *a, int *b);
void checkArray(int *array, int n);

void main( )
{
	// 파일 입출력과 반복문을 위한 변수
    FILE* fp;
	FILE* fop;
	int i = 0;
	int j = 0;

	// 텍스트 파일을 읽어오기 위한 변수.
	int *valueArray;
	int count = 1;

	// 시간 측정을 위한 변수
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

	// 텍스트 파일에 내용이 없을 때까지 읽어온 후 각각의 포인터 배열에 저장
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

	// 동적 할당을 해제하고, 파일 입출력을 끝내면서 프로그램 종료
}

// 퀵 정렬을 진행하는 메소드
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

// 실제로 원소를 이동시키면서 퀵 정렬을 처리해주는 메소드
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

// 배열의 안정화를 위해 랜덤한 원소를 처리하는 메소드
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

// 두 값을 바꿔주는 메소드
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 결과 출력을 위한 테스트 메소드
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