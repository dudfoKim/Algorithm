#include "head.h"
#include <time.h>

int deap[MAX_SIZE]; // Array of Deap
int deapMaxSize = 1; // Deap Size


int minPartner(int n){ // find the partner
	int h;
	for(h=2; 2*h<=n; h*=2);  // sibling 갯수를 count 
	return n-h/2; // deapMaxSize - sibling/2
}	

int maxPartner(int n){  // find the partner
	int h;
	for(h=2; 2*h<=n; h*=2);
	if (n+h/2<=deapMaxSize ) return n+h/2; // partner이 존재할 경우 리턴
	else return (n+h/2)/2; // 없으면 부모가 리턴 
}

int WhereHeap(int n){ // deapMaxSize가 Max or MinHeap 중 어디에 있는지 확인
	int h;
	for(h=2; 2*h<=n; h*=2);  // sibling 갯수를 count 
	if(n-h > h/2-1) return TRUE; // 절반이상? TRUE : FALSE
	else return FALSE;
}

void Insert(int item){
	int temp;
	int partner;
	deapMaxSize++;  // Insert 마다 Size증가 = 쓰일 배열의 크기 증가
	deap[deapMaxSize] = item;
	if(WhereHeap(deapMaxSize)){  // MaxHeap에 있는 경우
		partner = minPartner(deapMaxSize);  //minheap에 있는 partner 확인
		if(deap[deapMaxSize] < deap[partner]){  // 파트너와 비교해서 현재 값이 작으면 SWAP
			SWAP(deap[deapMaxSize], deap[partner], temp);
			adjustDeap(partner);  // Adjust deap
		}
	}
	else{  // Maxheap에 있는 경우
		partner = maxPartner(deapMaxSize);
		// partner이 Root가 아닌 경우 및 파트너보다 큰 경우
		if(partner!=1 && deap[deapMaxSize] > deap[partner]){
			SWAP(deap[deapMaxSize], deap[partner], temp);
			adjustDeap(partner);
		}
	}
	// 비교문이 끝나고 현재 deapMaxSize가 있는 위치의 deap을 재구성한다.
	adjustDeap(deapMaxSize);
}

void adjustDeap(int n){
	int i;
	int temp;
	if(WhereHeap(n)){  // MaxHeap에 있는 경우
		for(i=n; i>3; i/=2) // MaxHeap의 Root까지 반복하면서 부모값이 자식보다 작을경우
			if(deap[n] > deap[n/2]) SWAP(deap[n], deap[n/2], temp);
	}
	else{
		for(i=n; i>2; i/=2)
			if(deap[n] < deap[n/2]) SWAP(deap[n], deap[n/2], temp);
	}
}

int deleteMin(){
	int i, temp;
	if(deapMaxSize<2) printf("Error!!\n"), exit(0);
	temp=deap[2];  // MinHeap의 Root를 임시저장

	for(i=2; 2*i<=deapMaxSize; ) // deapMaxSize까지 반복
		if(2*i+1<=deapMaxSize){ // 오른 자식이 있을 때
			if(deap[i*2]<deap[i*2+1]){ // 두 자식값을 비교하여 작은값을 부모값에 저장
				deap[i] = deap[i*2], i=i*2;
			}
			else{
				deap[i] = deap[i*2+1], i=i*2+1;
			}
		}
		else{ // 왼쪽 자식만 있을때
			deap[i] = deap[i*2], i=i*2;
		}
	deap[i] = deap[deapMaxSize--]; // deapMaxSize를 줄인다.
	return temp; 
}

int deleteMax(){  // deleteMin()과 동일
	int i, temp;
	if(deapMaxSize<2) printf("Error!!\n"), exit(0);
	else if(deapMaxSize==2) deleteMin(); // deapMaxSize==2는 MinHeap의 Root idx이다.
	else{
		temp = deap[3];  // MaxHeap의 Root의 idx는 3이다.
		for(i=3; 2*i<=deapMaxSize; )
			if ( 2*i+1 <= deapMaxSize )
				if(deap[i*2] < deap[i*2+1]) deap[i]=deap[i*2+1], i=i*2+1;
				else deap[i]=deap[i*2], i=i*2;
			else{
				deap[i]=deap[i*2], i=i*2;
			}
		deap[i] = deap[deapMaxSize--];
	}
	return temp;
}

void print(){
	int i, j;
	printf("====PRINT QUEUE====\n");
	// Tree의 level의 sibling의 갯수만큼 한줄씩 출력
	for(i=2, j=4; i<=deapMaxSize; i++){
		if(i==j) printf("\n"), j*=2;  // sibling 출력에 대한 레벨증가 및 sibling*2
		printf("%d  ", deap[i]);
	}
}

void printSortedOrder(){ // Heap, Deap Sort 출력
	int i, j;
	int p, temp, heap[128];
	clock_t start, end;

	for(i=0; i<=deapMaxSize; i++) heap[i] = deap[i+1];  // Deap->Heap 복사

	printf("====PRINT Sorted Order====\n");
	printf("[Using HeapSort]\n");

	start = clock(); // heap에 대한 start clock

	for(i=2; i<=deapMaxSize-1; i++)
	for(j=i; heap[j/2]<heap[j] && j>1; j/=2) SWAP(heap[j/2], heap[j], temp);
	//부모와 자식값을 비교하면서 MAX_Heap 생성

	for(i=1; i<deapMaxSize-1; i++){
		SWAP(heap[1], heap[deapMaxSize-i], temp);  // Root <-> deapMaxSize-1을 변경
		for(j=1; j*2<deapMaxSize-1-i; ) // (deapMaxSize-1)-i 이후는 정렬되있으므로, 이전까지 정렬
			if(j*2+1<=deapMaxSize-1-i) // 왼쪽, 오른쪽 자식이 모두 존재할때
				if(heap[j*2] > heap[j*2+1]) // 큰 값을 찾아 다시 자신과 비교하여 SWAP
					if(heap[j*2] > heap[j]) SWAP(heap[j], heap[j*2], temp), j*=2;
					else break;
				else
					if(heap[j*2+1] > heap[j]) SWAP(heap[j], heap[j*2+1], temp), j=j*2+1;
					else break;
			else // 왼쪽자식만 있을때
				if(heap[j*2] > heap[j]) SWAP(heap[j], heap[j*2], temp), j*=2;
	}

	for(i=1; i<deapMaxSize; i++) printf("%3d\n", heap[i]);
	end = clock();

	printf("Duration : %.3lf\n", (double)(end-start)/CLK_TCK);
	printf("[Using Deap's Deletion]\n");
	
	p=deapMaxSize;  // deleteMin()에서 deapMaxSize를 -1 하므로 p에 저장해서 사용
	
	start = clock(); // deap에 대한 start clock
	for(i=2; i<=p; i++){
		printf("%3d\n", deleteMin());
	}
	end = clock();

	printf("Deap is empty\n");
	printf("Duration : %.3lf\n", (double)(end-start)/CLK_TCK);
}