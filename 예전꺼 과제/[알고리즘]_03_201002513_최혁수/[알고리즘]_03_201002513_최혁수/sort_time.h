#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 2byte 표현값 -32768~32767으로 MAX, MIN 정의                                  */
/* 추가적으로, 각 정렬에 필요한 1차원 배열의 크기로 쓰이는 MAX, MIN 이므로 */
/* 컴파일러는 정적할당에 한계치를 0x7FFFFFFF 약 1MB(1,000,000)로 둔다         */
#define MAX_INT 32767
#define MIN_INT -32768

clock_t start, stop; // clock()에 의해 계산된 초당 시간주기(clock ticks)의 수를 나타낸다.
double duration;

/* 각 정렬에 쓰이는 배열 */
int bubbleData[MAX_INT];
int insertionData[MAX_INT];
int quickData[MAX_INT];

/* 정렬함수 정의 */
void bubbleSort(int*, int);
void insertionSort(int *, int);
void quickSort(int*, int, int);

/* 정렬에 대한 clock ticks를 구하는 함수 */
void sortTest(int*, int*, int*, int);

/* 난수구현 */
void createRandomNum(int*, int*, int*, int);
