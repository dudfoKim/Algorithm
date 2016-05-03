#include <stdio.h>
#include <stdlib.h>
 
void merge(int *array,int first,int mid,int last);
void sort(int *array,int first,int last);
void printArray(int *array, int n);

void main( )
{
    FILE* fp;
	FILE* fop;
	int i = 0;
	int *array;
	int count = 1;
 	array = (int*)malloc(sizeof(int)*count);

	fp = fopen("data02.txt", "rt");
	fop = fopen("00_201102412_Merge.txt", "wt");

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

	printf("=====Using the Merge sort=====");

	printf("\n\nShow the array before sorting :");
	printArray(array, count-1);

	sort(array, 0, count-2);

	printf("\n\nShow the sorted array result :");
	printArray(array, count-1);

	printf("\nMerge sort Finish!\n\n");

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

void merge(int *array,int first,int mid,int last)
{
	int FIdx = first;
	int RIdx = mid+1;
	int SIdx = first;
	int i = 0;
	int *SortedArr = (int *)malloc( (last+1)*sizeof(int));

	while(FIdx<=mid && RIdx<=last)
	{
		if(array[FIdx] <= array[RIdx])
		{
			SortedArr[SIdx] = array[FIdx++];
		}
		else
		{
			SortedArr[SIdx] = array[RIdx++];
		}

		SIdx++;
	}

	if(FIdx>mid)
	{
		for(i=RIdx;i<=last;i++,SIdx++)
		{
			SortedArr[SIdx] = array[i];
		}
	}
	else
	{
		for(i=FIdx;i<=mid;i++,SIdx++)
		{
			SortedArr[SIdx] = array[i];
		}
	}

	for(i=first;i<=last;i++)
	{
		array[i] = SortedArr[i];
	}

	SortedArr = NULL;
	free(SortedArr);
}

void sort(int *array,int first,int last)
{
	if(first<last)
	{
		int mid = (first+last)/2;

		sort(array,first,mid);
		sort(array,mid+1,last);
		merge(array,first,mid,last);
	}
}