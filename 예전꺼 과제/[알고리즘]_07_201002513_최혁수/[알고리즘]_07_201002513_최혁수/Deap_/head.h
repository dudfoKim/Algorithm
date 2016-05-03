#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 128  // MAX_SIZE 정의
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define TRUE 1  // boolean 함수 대체
#define FALSE 0

int minPartner(int n);
int maxPartner(int n);
int WhereHeap(int n);  // deapMaxSize가 Min or Maxheap 어느위치에 있는지 확인
void Insert(int item);  
void adjustDeap(int n); // heap 재조정
int deleteMin();
int deleteMax();
void print();
void printSortedOrder();  // heap sort -> deap sort 순으로 print