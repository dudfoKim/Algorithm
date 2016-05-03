#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 2byte ǥ���� -32768~32767���� MAX, MIN ����                                  */
/* �߰�������, �� ���Ŀ� �ʿ��� 1���� �迭�� ũ��� ���̴� MAX, MIN �̹Ƿ� */
/* �����Ϸ��� �����Ҵ翡 �Ѱ�ġ�� 0x7FFFFFFF �� 1MB(1,000,000)�� �д�         */
#define MAX_INT 32767
#define MIN_INT -32768

clock_t start, stop; // clock()�� ���� ���� �ʴ� �ð��ֱ�(clock ticks)�� ���� ��Ÿ����.
double duration;

/* �� ���Ŀ� ���̴� �迭 */
int bubbleData[MAX_INT];
int insertionData[MAX_INT];
int quickData[MAX_INT];

/* �����Լ� ���� */
void bubbleSort(int*, int);
void insertionSort(int *, int);
void quickSort(int*, int, int);

/* ���Ŀ� ���� clock ticks�� ���ϴ� �Լ� */
void sortTest(int*, int*, int*, int);

/* �������� */
void createRandomNum(int*, int*, int*, int);
