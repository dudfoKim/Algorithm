#include "sort_time.h"

void createRandomNum(int* bubbleData, int* insertionData, int* quickData, int totalNum){
	 int data;
	 int i;
	 srand((unsigned)time(NULL));  // �����߻�
     quickData[totalNum] = MAX_INT; // �ִ밪 ����
	 
	 for(i=0; i<totalNum; i++){  // totalNum ������ŭ ���� �߻���, �� ���Ŀ� ���� ������ ����
		data = rand() % RAND_MAX;
		bubbleData[i] = data;
		insertionData[i] = data;
		quickData[i] = data;
	 }
}
/* �������� */
void bubbleSort(int *bubbleData, int totalNum){
	int count = totalNum -1;
	int temp;
	int i, j;

	for(i=0; i<count; i++)
		for(j=i+1; j<totalNum; j++){  // i+1 ~ totalNum-1 �ݺ�
			if(bubbleData[i]>bubbleData[j]){  // ��, �� ���� ������ ũ�� Swap.
				temp=bubbleData[i];
				bubbleData[i]=bubbleData[j];
				bubbleData[j]=temp;
			}
		}
}

/* �������� */
void insertionSort(int* insertionData, int totalNum)
{
  int i, j;
  int temp;
  for (i = 1; i<totalNum; i++ )
  {
    temp = insertionData[(j=i)];  // insertionData[1]���� temp ����, ù �������� �� ������
    /* �����Ͱ��� ���� ���� ���ذ��鼭 ���� ���� Ŭ�� Swap ��� */
	while (--j>=0 && temp<insertionData[j]) insertionData[j+1] = insertionData[j];
	/* ������ ���� �� �����ؾ� �� ��ġ�� ù temp ���� ���� �ִ´�. */
    insertionData[j+1] = temp;
  }
}

/* �� ���� */
void quickSort(int* quickData, int left, int right)
 {
   /* Left_Num, Right_Num = �� ����, ������ ���� �����ϱ� ���� ���� */
   int pivot, Left_Num, Right_Num;
   Left_Num = left;
   Right_Num = right;
   /* ù �߰����� �� ���� ������ ���� */
   pivot = quickData[left];

   /* left, right ���� ������, �������� Ž���ذ��鼭 ū���� ã�Ƴ��µ�, */
   /* ����, �������� ��Ÿ���� ���� ���� �ڹٲ�, �� left���� right������ �� �����ʿ� ���������� ���� */
   while (left < right)
   {
	 /* �ǹ����� ���� �����ʰ��� ��Ÿ�������� �˻� */
     while ((quickData[right] >= pivot) && (left < right)) right--;
	 /* ���ʰ��� �����ʰ��� ���� */
     if (left != right)
     {
       quickData[left] = quickData[right];
       left++;
     }
	 /* �ǹ����� ū ���ʰ��� ��Ÿ�������� �˻� */
     while ((quickData[left] <= pivot) && (left < right)) left++;
	 /* �����ʰ��� ���ʰ��� ���� */
     if (left != right)
     {
       quickData[right] = quickData[left];
       right--;
     }
   }
   /* �ǹ��� ����ġ�� ����, quickData[left] ���������� �ǹ����� �۴� */
   quickData[left] = pivot;
   /* ���� pivot�� ��������, left<pivot<right �� ������ ũ�⸦ ������. */
   pivot = left;
   left = Left_Num;
   right = Right_Num;

   /* pivot�� �������� ������ ���� left, right �����͵��� ��������� �ٽ� ���� */
   if (left < pivot)
     quickSort(quickData, left, pivot-1);
   if (right > pivot)
     quickSort(quickData, pivot+1, right);
}

/* �� ���ĺ� �ð��ֱ� Ž�� */
void sortTest(int* bubbleData, int* insertionData, int* quickData, int totalNum)
{
	printf("Number = %d\n", totalNum);
	createRandomNum(bubbleData, insertionData, quickData, totalNum);
	start = clock();  // star ~ stop = bubbleSort()�� �ð��ֱ� Ž��
	bubbleSort(bubbleData, totalNum);
	stop = clock();
	duration = (((double)(stop-start))/CLK_TCK)*10;
	printf("Bubble Time : %f\n", duration);

	start = clock();
	insertionSort(insertionData, totalNum);
	stop = clock();
	duration = (((double)(stop-start))/CLK_TCK)*10;
	printf("insertion Time : %f\n", duration);

	start = clock();
	quickSort(quickData, 0, totalNum);
	stop = clock();
	duration = (((double)(stop-start))/CLK_TCK)*10;
	printf("quick Time : %f\n", duration);
	
	printf("\n");
}