// 소스 코드 구현을 위한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 소스 코드 구현을 위한 함수 선언
int* splitArray(int value, int n);
int lengthArray(int *array);
int lengthNumber(int n);
void printArray(int *array, int n);
void printCharArray(char *array, int n);
void swap(int *a, int *b);
int left(int i);
int right(int i);

// 힙 정렬 구현을 위한 함수 선언
void insert(int *array, int value);
int H_max(int *array);
int extract_max(int *array);
void increase_key(int *array, int value, int key);
void H_delete(int *array, int index);
void build_max_heap(int* array);
void complete_heap_sort(int *array);
void max_heapify(int *array, int i);

// insert 함수를 사용하기 위한 변수
int plus = 0;

// extract_max 함수를 사용하기 위한 변수
int minus = 0;

// h_delete 함수를 사용하기 위한 변수
int num = 0;

	FILE* fop;

void main( )
{
	// 파일 입출력과 반복문을 위한 변수
    FILE* fp;

	int i = 0;
	int j = 0;

	// 텍스트 파일을 읽어오기 위한 변수.
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

	// 텍스트 파일에 내용이 없을 때까지 읽어온 후 각각의 포인터 배열에 저장
	while(!feof(fp))
	{
		functionArray = (char*)realloc(functionArray, sizeof(char)*count);
		valueArray = (int*)realloc(valueArray, sizeof(int)*count);

		fscanf(fp, "%c.%d, ", &(functionArray[count-1]), &(valueArray[count-1]));
		count++;
	}

	// 배열에 내용이 있을 때까지 계속 출력하는 부분
	while(j<count-1)
	{
		// 숫자를 계속 쪼갠 후 임시 변수에 저장
		int *realValue = splitArray(valueArray[j], lengthNumber(valueArray[j]));

		// 영어 문자열에 따라 case를 나눠서 조건에 맞춰서 구현
		switch(functionArray[j])
		{
			// a ~ g까지 따로 구현
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
			// a ~ f가 아닐 경우 에러 메시지 출력
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

	// 동적 할당을 해제하고, 파일 입출력을 끝내면서 프로그램 종료
}

// 배열의 맨 끝에 한 개의 element를 추가하는 메소드(값은 항상 9로 고정)
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

// 최대 힙을 만든 후, 가장 큰 값을 얻어내는 메소드
int H_max(int *array)
{
	build_max_heap(array);

	return array[0];
}

// 가장 큰 원소를 삭제한 후 최대 힙을 만들어주는 메소드
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

// 지정한 index의 값을 바꾸고 최대 힙을 만들어주는 메소드
void increase_key(int *array, int index, int value)
{
	array[index-1] = value;

	build_max_heap(array);
}

// 지정한 index의 값을 삭제하고 최대 힙을 만들어주는 메소드
void H_delete(int *array, int index)
{
	int temp = array[lengthArray(array)-1];
	num++;

	swap(&array[index-1], &array[lengthArray(array)-1]);
	array = (int*)realloc(array, sizeof(int)*lengthArray(array)-1);

	build_max_heap(array);
}

// 최대 힙을 만들기 위한 메소드
void build_max_heap(int *array)
{
	int i = 0;

	for(i=lengthArray(array)/2; i>=0; i--)
	{
		max_heapify(array, i);
	}
}

// 내림차순으로 힙정렬을 하기 위한 메소드
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

// 최대 힙을 만들어주는 메소드
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

// 각각 왼쪽, 오른쪽 자식의 index를 얻어오기 위한 메소드
int left(int i)
{
	return 2*i+1;
}

int right(int i)
{
	return 2*i+2;
}

// 두 값을 서로 바꿔주는 메소드
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 긴 숫자 값을 잘라서 각각 따로 저장하는 메소드
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

// 배열의 길이를 알아내는 메소드
int lengthArray(int *array)
{
	int size;
	size = *(array - sizeof(int));
	
	return size/4;
}

// 숫자의 길이를 알아내는 메소드
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

// int형 배열의 값을 출력하는 메소드
void printArray(int *array, int n)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}

// char형 배열의 값을 출력하는 메소드
void printCharArray(char *array, int n)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%c ", array[i]);
	}

	printf("\n");
}