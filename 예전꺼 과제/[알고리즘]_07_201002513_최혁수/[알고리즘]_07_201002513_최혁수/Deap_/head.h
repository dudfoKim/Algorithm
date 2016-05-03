#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 128  // MAX_SIZE ����
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define TRUE 1  // boolean �Լ� ��ü
#define FALSE 0

int minPartner(int n);
int maxPartner(int n);
int WhereHeap(int n);  // deapMaxSize�� Min or Maxheap �����ġ�� �ִ��� Ȯ��
void Insert(int item);  
void adjustDeap(int n); // heap ������
int deleteMin();
int deleteMax();
void print();
void printSortedOrder();  // heap sort -> deap sort ������ print