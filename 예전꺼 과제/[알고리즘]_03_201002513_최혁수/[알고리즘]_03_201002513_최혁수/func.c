#include "sort_time.h"

void createRandomNum(int* bubbleData, int* insertionData, int* quickData, int totalNum){
	 int data;
	 int i;
	 srand((unsigned)time(NULL));  // 난수발생
     quickData[totalNum] = MAX_INT; // 최대값 대입
	 
	 for(i=0; i<totalNum; i++){  // totalNum 갯수만큼 난수 발생후, 각 정렬에 쓰일 변수에 저장
		data = rand() % RAND_MAX;
		bubbleData[i] = data;
		insertionData[i] = data;
		quickData[i] = data;
	 }
}
/* 버블정렬 */
void bubbleSort(int *bubbleData, int totalNum){
	int count = totalNum -1;
	int temp;
	int i, j;

	for(i=0; i<count; i++)
		for(j=i+1; j<totalNum; j++){  // i+1 ~ totalNum-1 반복
			if(bubbleData[i]>bubbleData[j]){  // 좌, 우 비교후 좌측이 크면 Swap.
				temp=bubbleData[i];
				bubbleData[i]=bubbleData[j];
				bubbleData[j]=temp;
			}
		}
}

/* 삽입정렬 */
void insertionSort(int* insertionData, int totalNum)
{
  int i, j;
  int temp;
  for (i = 1; i<totalNum; i++ )
  {
    temp = insertionData[(j=i)];  // insertionData[1]값을 temp 저장, 첫 삽입정렬 비교 데이터
    /* 데이터값과 앞의 수를 비교해가면서 앞의 값이 클때 Swap 기능 */
	while (--j>=0 && temp<insertionData[j]) insertionData[j+1] = insertionData[j];
	/* 정렬이 끝난 후 삽입해야 될 위치에 첫 temp 저장 값을 넣는다. */
    insertionData[j+1] = temp;
  }
}

/* 퀵 정렬 */
void quickSort(int* quickData, int left, int right)
 {
   /* Left_Num, Right_Num = 맨 왼쪽, 오른쪽 값을 유지하기 위한 변수 */
   int pivot, Left_Num, Right_Num;
   Left_Num = left;
   Right_Num = right;
   /* 첫 중간값은 맨 왼쪽 값으로 지정 */
   pivot = quickData[left];

   /* left, right 각각 오른쪽, 왼쪽으로 탐색해가면서 큰값을 찾아내는데, */
   /* 왼쪽, 오른쪽을 나타내는 값이 서로 뒤바뀔때, 즉 left값이 right값보다 더 오른쪽에 있을때까지 수행 */
   while (left < right)
   {
	 /* 피벗보다 작은 오른쪽값이 나타날때까지 검색 */
     while ((quickData[right] >= pivot) && (left < right)) right--;
	 /* 왼쪽값에 오른쪽값을 저장 */
     if (left != right)
     {
       quickData[left] = quickData[right];
       left++;
     }
	 /* 피벗보다 큰 왼쪽값이 나타날때까지 검색 */
     while ((quickData[left] <= pivot) && (left < right)) left++;
	 /* 오른쪽값에 왼쪽값을 저장 */
     if (left != right)
     {
       quickData[right] = quickData[left];
       right--;
     }
   }
   /* 피벗을 재위치에 저장, quickData[left] 이전값들은 피벗보다 작다 */
   quickData[left] = pivot;
   /* 현재 pivot을 기준으로, left<pivot<right 의 데이터 크기를 가진다. */
   pivot = left;
   left = Left_Num;
   right = Right_Num;

   /* pivot을 기준으로 반으로 나뉜 left, right 데이터들을 재귀적으로 다시 정렬 */
   if (left < pivot)
     quickSort(quickData, left, pivot-1);
   if (right > pivot)
     quickSort(quickData, pivot+1, right);
}

/* 각 정렬별 시간주기 탐색 */
void sortTest(int* bubbleData, int* insertionData, int* quickData, int totalNum)
{
	printf("Number = %d\n", totalNum);
	createRandomNum(bubbleData, insertionData, quickData, totalNum);
	start = clock();  // star ~ stop = bubbleSort()의 시간주기 탐색
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