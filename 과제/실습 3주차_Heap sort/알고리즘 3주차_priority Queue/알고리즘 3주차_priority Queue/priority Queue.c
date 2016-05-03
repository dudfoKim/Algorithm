// �ҽ� �ڵ� ������ ���� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// �ҽ� �ڵ� ������ ���� �Լ� ����
int* splitArray(int value, int n);
int lengthArray(int *array);
int lengthNumber(int n);
void printArray(int *array, int n);
void printCharArray(char *array, int n);
void swap(int *a, int *b);
int left(int i);
int right(int i);

// �� ���� ������ ���� �Լ� ����
void insert(int *array, int value);
int H_max(int *array);
int extract_max(int *array);
void increase_key(int *array, int value, int key);
void H_delete(int *array, int index);
void build_max_heap(int* array);
void complete_heap_sort(int *array);
void max_heapify(int *array, int i);

// insert �Լ��� ����ϱ� ���� ����
int plus = 0;

// extract_max �Լ��� ����ϱ� ���� ����
int minus = 0;

// h_delete �Լ��� ����ϱ� ���� ����
int num = 0;

	FILE* fop;

void main( )
{
	// ���� ����°� �ݺ����� ���� ����
    FILE* fp;

	int i = 0;
	int j = 0;

	// �ؽ�Ʈ ������ �о���� ���� ����.
	char *functionArray;
	int *valueArray;
	int count = 1;

	functionArray = (char*)malloc(sizeof(char));
	valueArray = (int*)malloc(sizeof(int));

	fp = fopen("data03.txt", "rt");
	fop = fopen("00_201102412_priority.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");

		return;
	}

	// �ؽ�Ʈ ���Ͽ� ������ ���� ������ �о�� �� ������ ������ �迭�� ����
	while(!feof(fp))
	{
		functionArray = (char*)realloc(functionArray, sizeof(char)*count);
		valueArray = (int*)realloc(valueArray, sizeof(int)*count);

		fscanf(fp, "%c.%d, ", &(functionArray[count-1]), &(valueArray[count-1]));
		count++;
	}

	// �迭�� ������ ���� ������ ��� ����ϴ� �κ�
	while(j<count-1)
	{
		// ���ڸ� ��� �ɰ� �� �ӽ� ������ ����
		int *realValue = splitArray(valueArray[j], lengthNumber(valueArray[j]));

		// ���� ���ڿ��� ���� case�� ������ ���ǿ� ���缭 ����
		switch(functionArray[j])
		{
			// a ~ g���� ���� ����
			case 'a':
			{
				printf("----- a. Insert the element -----\n\n");

				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				insert(realValue, 9);

				printf("\nModified Array : ");
				printArray(realValue, lengthArray(realValue)+plus);

				for(i=0; i<lengthArray(realValue)+plus; i++)
				{
					fprintf(fop, "%d", realValue[i]);
				}

				fprintf(fop, ", ");

				plus = 0;

				break;
			}
			case 'b':
			{
				printf("\n----- b. Get Largest element -----\n\n");

				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				printf("\nMax : %d\n", H_max(realValue));

				printf("\nModified Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				for(i=0; i<lengthArray(realValue); i++)
				{
					fprintf(fop, "%d", realValue[i]);
				}

				fprintf(fop, ", ");

				break;
			}
			case 'c':
			{
				printf("\n----- c. Do heap sort and delete the root -----\n\n");
				
				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				extract_max(realValue);

				printf("\nModified Array : ");
				printArray(realValue, lengthNumber(valueArray[j])-minus);

				for(i=0; i<lengthArray(realValue); i++)
				{
					fprintf(fop, "%d", realValue[i]);
				}

				fprintf(fop, ", ");

				break;
			}
			case 'd':
			{
				printf("\n----- d. Change the element -----\n\n");

				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));
				
				increase_key(realValue, 1, 5);
				
				printf("\nModified Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				for(i=0; i<lengthArray(realValue); i++)
				{
					fprintf(fop, "%d", realValue[i]);
				}

				fprintf(fop, ", ");

				break;
			}
			case 'e':
			{
				printf("\n----- e. Delete the element -----\n\n");

				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				H_delete(realValue, 5);

				printf("\nModified Array : ");
				printArray(realValue, lengthNumber(valueArray[j])-num);

				for(i=0; i<lengthArray(realValue); i++)
				{
					fprintf(fop, "%d", realValue[i]);
				}

				fprintf(fop, ", ");

				break;
			}
			case 'f':
			{
				printf("\n----- f. Do heap sort -----\n\n");

				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				for(i=0; i<lengthArray(realValue); i++)
				{
					fprintf(fop, "%d", realValue[i]);
				}

				fprintf(fop, ", ");

				break;
			}
			case 'g':
			{
				printf("\n----- g. Sorting the array -----\n\n");

				printf("Original Array : ");
				printArray(realValue, lengthNumber(valueArray[j]));

				complete_heap_sort(realValue);

				fprintf(fop, ", ");

				break;
			}
			// a ~ f�� �ƴ� ��� ���� �޽��� ���
			default:
			{
				printf("ERROR!\n");
			}
		}

		realValue = NULL;
		free(realValue);

		j++;
	}

	printf("\n");

	fclose(fp);

	functionArray = NULL;
	free(functionArray);

	valueArray = NULL;
	free(valueArray);

	// ���� �Ҵ��� �����ϰ�, ���� ������� �����鼭 ���α׷� ����
}

// �迭�� �� ���� �� ���� element�� �߰��ϴ� �޼ҵ�(���� �׻� 9�� ����)
void insert(int *array, int value)
{
	int index = lengthArray(array) + plus;
	int *temp = (int*)malloc(sizeof(int)*(index));
	temp = array;
	plus++;

	temp[index] = value;

	memcpy(array, temp, index);

	temp = NULL;
	free(temp);
}

// �ִ� ���� ���� ��, ���� ū ���� ���� �޼ҵ�
int H_max(int *array)
{
	build_max_heap(array);

	return array[0];
}

// ���� ū ���Ҹ� ������ �� �ִ� ���� ������ִ� �޼ҵ�
int extract_max(int *array)
{
	int max = 0;
	minus++;

	build_max_heap(array);

	max = array[0];
	swap(&array[0], &array[lengthArray(array)-1]);

	array = (int*)realloc(array, sizeof(int)*lengthArray(array)-1);
	build_max_heap(array);
	
	return max;
}

// ������ index�� ���� �ٲٰ� �ִ� ���� ������ִ� �޼ҵ�
void increase_key(int *array, int index, int value)
{
	array[index-1] = value;

	build_max_heap(array);
}

// ������ index�� ���� �����ϰ� �ִ� ���� ������ִ� �޼ҵ�
void H_delete(int *array, int index)
{
	int temp = array[lengthArray(array)-1];
	num++;

	swap(&array[index-1], &array[lengthArray(array)-1]);
	array = (int*)realloc(array, sizeof(int)*lengthArray(array)-1);

	build_max_heap(array);
}

// �ִ� ���� ����� ���� �޼ҵ�
void build_max_heap(int *array)
{
	int i = 0;

	for(i=lengthArray(array)/2; i>=0; i--)
	{
		max_heapify(array, i);
	}
}

// ������������ �������� �ϱ� ���� �޼ҵ�
void complete_heap_sort(int *array)
{
	int i = 0;
	int size = lengthArray(array);
	int *temp = (int*)malloc(sizeof(int)*size);

	while(i<size)
	{
		temp[i] = extract_max(array);
		i++;
	}

	printf("\nModified Array : ");
	printArray(temp, size);

	
	for(i=0; i<lengthArray(temp); i++)
	{
		fprintf(fop, "%d", temp[i]);
	}

	temp = NULL;
	free(temp);
}

// �ִ� ���� ������ִ� �޼ҵ�
void max_heapify(int *array, int i)
{
	int l = left(i);
	int r = right(i);
	int max;

	if(l<=lengthArray(array) && array[l]>array[i])
	{
		max = l;
	}
	else
	{
		max = i;
	}
	if(r<=lengthArray(array) && array[r]>array[max])
	{
		max = r;
	}
	if(max!=i)
	{
		swap(&array[i], &array[max]);	
		max_heapify(array, max);
	}
}

// ���� ����, ������ �ڽ��� index�� ������ ���� �޼ҵ�
int left(int i)
{
	return 2*i+1;
}

int right(int i)
{
	return 2*i+2;
}

// �� ���� ���� �ٲ��ִ� �޼ҵ�
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// �� ���� ���� �߶� ���� ���� �����ϴ� �޼ҵ�
int* splitArray(int value, int n)
{
	int i = 0;
	int ten = 10;
	int *tempArray = (int*)malloc(sizeof(int)*n);
	int *realArray = (int*)malloc(sizeof(int)*n);

	while(value)
	{
		tempArray[i] = value%10;
		value /= 10;
		i++;
	}

	for(i=0; i<n; i++)
	{
		realArray[i] = tempArray[n-i-1];
	}

	tempArray = NULL;
	free(tempArray);

	return realArray;

	realArray = NULL;
	free(tempArray);
}

// �迭�� ���̸� �˾Ƴ��� �޼ҵ�
int lengthArray(int *array)
{
	int size;
	size = *(array - sizeof(int));
	
	return size/4;
}

// ������ ���̸� �˾Ƴ��� �޼ҵ�
int lengthNumber(int n)
{
	int i = 0;
	int ten = 10;
	int length = 1;

	while(n/ten)
	{
		length++;
		ten *= 10;
	}

	return length;
}

// int�� �迭�� ���� ����ϴ� �޼ҵ�
void printArray(int *array, int n)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}

// char�� �迭�� ���� ����ϴ� �޼ҵ�
void printCharArray(char *array, int n)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%c ", array[i]);
	}

	printf("\n");
}