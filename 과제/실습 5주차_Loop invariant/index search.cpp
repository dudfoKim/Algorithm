#include <stdio.h>
#include <stdlib.h>

// 메소드 선언
int binarySearch(int *array, int n, int key);
void printArray(int *array, int n);

void main()
{
	// 배열의 완성을 위한 선언
	int *array = (int*)malloc(sizeof(int));
	int num;
	int key;
	int i = 0;
	int j = 5;
	int result = -1;

	// 배열의 크기를 입력
	printf("Input the size for array : ");
	scanf("%d", &num);
	
	array = (int*)realloc(array, sizeof(int)*num);

	for(i=0; i<num; i++)
	{
		array[i] = j;
		j= j+5;
	}

	printf("\nOriginal array : ");
	printArray(array, num);

	// 배열에서 찾고 싶은 값을 입력
	printf("\nInput the value for key : ");
	scanf("%d", &key);

	// 이진탐색한 결과값에 +1 한 값을 변수에 저장(배열의 index는 0부터 시작하므로)
	result = binarySearch(array, num, key) + 1;

	// 입력한 값이 배열에서 없을 경우 에러
	if(result!=0)
	{
		printf("\n=> input value : %d, value index : %d\n\n", array[result-1], result);
	}
	else
	{
		printf("\n=> You can't find this value in array!\n\n");
	}
}

// 받아온 값의 인덱스를 배열에서 찾아 반환하는 메소드
int binarySearch(int *array, int num, int key)
{
	int left = 0;
	int right = num-1;
	int middle;   

	while(left<=right)
	{
		middle = (left+right)/2;

		if(array[middle]==key)
		{
			return middle;
		}
		else if(array[middle]>key)
		{
			right = middle - 1;
		}
		else if(array[middle]<key)
		{
			left = middle + 1;
		}
	}

	return -1;
}

// 배열을 출력하는 메소드
void printArray(int *array, int n)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}