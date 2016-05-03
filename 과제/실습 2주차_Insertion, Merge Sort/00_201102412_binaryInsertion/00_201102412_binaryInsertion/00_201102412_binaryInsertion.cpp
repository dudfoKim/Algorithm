#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int binarySearch (int *array, int left, int right, int key);
void sort (int *array, int n);
void printArray(int *array, int n);

void main( )
{
    FILE* fp;
	FILE* fop;

	int i = 0;
	int *array;
	int count = 1;
 	array = (int*)malloc(sizeof(int)*count);

	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);

	fp = fopen("data02.txt", "rt");
	fop = fopen("00_201102412_binaryInsertion.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");

		return;
	}

	while(!feof(fp))
	{
		array = (int*)realloc(array, sizeof(int)*count);
		fscanf(fp, "%d,", &(array[count-1]));
		count++;
	}

	array = (int*)realloc(array, sizeof(int)*(count-1));

	printf("=====Using the binaryInsertion sort=====");

	printf("\n\nShow the array before sorting :");
	printArray(array, count-1);

	QueryPerformanceCounter(&start);
	sort(array, count-1);
	QueryPerformanceCounter(&end);

	printf("\n\nShow the sorted array result :");
	printArray(array, count-1);

	printf("\nRequired %.6f seconds\n", (float)(end.QuadPart-start.QuadPart)/freq.QuadPart);
	printf("\nbinaryInsertion sort Finish!\n\n");

	for(i=0; i<count-1; i++)
	{
		fprintf(fop, "%d,", array[i]);
	}

	fclose(fp);

	array = NULL;
	free(array);
}

void printArray(int *array, int n)
{
	int i = 0;

	printf("\n");

	for(i=0; i<n; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}

void sort(int *array, int n)
{
    int i = 0;
	int j = 0;
	int output = 0;
    int temp = 0;

    for(i=1; i<n; i++) 
	{
        output = binarySearch(array, 0, i, array[i]);
        temp = array[i];

        for(j=i-1; j>=output; j--)
		{
            array[j + 1] = array[j];
		}

        array[output] = temp;
    }
}

int binarySearch(int *array, int left, int right, int key)
{
    int mid;

    if(left==right)
	{
        return left;
	}

    mid = left + ((right-left)/2);

    if(key>array[mid])
	{
        return binarySearch(array, mid+1, right, key);
	}
    else if(key<array[mid])
	{
        return binarySearch(array, left, mid, key);
	}

    return mid;
}