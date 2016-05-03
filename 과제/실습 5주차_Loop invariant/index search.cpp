#include <stdio.h>
#include <stdlib.h>

// �޼ҵ� ����
int binarySearch(int *array, int n, int key);
void printArray(int *array, int n);

void main()
{
	// �迭�� �ϼ��� ���� ����
	int *array = (int*)malloc(sizeof(int));
	int num;
	int key;
	int i = 0;
	int j = 5;
	int result = -1;

	// �迭�� ũ�⸦ �Է�
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

	// �迭���� ã�� ���� ���� �Է�
	printf("\nInput the value for key : ");
	scanf("%d", &key);

	// ����Ž���� ������� +1 �� ���� ������ ����(�迭�� index�� 0���� �����ϹǷ�)
	result = binarySearch(array, num, key) + 1;

	// �Է��� ���� �迭���� ���� ��� ����
	if(result!=0)
	{
		printf("\n=> input value : %d, value index : %d\n\n", array[result-1], result);
	}
	else
	{
		printf("\n=> You can't find this value in array!\n\n");
	}
}

// �޾ƿ� ���� �ε����� �迭���� ã�� ��ȯ�ϴ� �޼ҵ�
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

// �迭�� ����ϴ� �޼ҵ�
void printArray(int *array, int n)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}