#include "head.h"
#include <time.h>

int deap[MAX_SIZE]; // Array of Deap
int deapMaxSize = 1; // Deap Size


int minPartner(int n){ // find the partner
	int h;
	for(h=2; 2*h<=n; h*=2);  // sibling ������ count 
	return n-h/2; // deapMaxSize - sibling/2
}	

int maxPartner(int n){  // find the partner
	int h;
	for(h=2; 2*h<=n; h*=2);
	if (n+h/2<=deapMaxSize ) return n+h/2; // partner�� ������ ��� ����
	else return (n+h/2)/2; // ������ �θ� ���� 
}

int WhereHeap(int n){ // deapMaxSize�� Max or MinHeap �� ��� �ִ��� Ȯ��
	int h;
	for(h=2; 2*h<=n; h*=2);  // sibling ������ count 
	if(n-h > h/2-1) return TRUE; // �����̻�? TRUE : FALSE
	else return FALSE;
}

void Insert(int item){
	int temp;
	int partner;
	deapMaxSize++;  // Insert ���� Size���� = ���� �迭�� ũ�� ����
	deap[deapMaxSize] = item;
	if(WhereHeap(deapMaxSize)){  // MaxHeap�� �ִ� ���
		partner = minPartner(deapMaxSize);  //minheap�� �ִ� partner Ȯ��
		if(deap[deapMaxSize] < deap[partner]){  // ��Ʈ�ʿ� ���ؼ� ���� ���� ������ SWAP
			SWAP(deap[deapMaxSize], deap[partner], temp);
			adjustDeap(partner);  // Adjust deap
		}
	}
	else{  // Maxheap�� �ִ� ���
		partner = maxPartner(deapMaxSize);
		// partner�� Root�� �ƴ� ��� �� ��Ʈ�ʺ��� ū ���
		if(partner!=1 && deap[deapMaxSize] > deap[partner]){
			SWAP(deap[deapMaxSize], deap[partner], temp);
			adjustDeap(partner);
		}
	}
	// �񱳹��� ������ ���� deapMaxSize�� �ִ� ��ġ�� deap�� �籸���Ѵ�.
	adjustDeap(deapMaxSize);
}

void adjustDeap(int n){
	int i;
	int temp;
	if(WhereHeap(n)){  // MaxHeap�� �ִ� ���
		for(i=n; i>3; i/=2) // MaxHeap�� Root���� �ݺ��ϸ鼭 �θ��� �ڽĺ��� �������
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
	temp=deap[2];  // MinHeap�� Root�� �ӽ�����

	for(i=2; 2*i<=deapMaxSize; ) // deapMaxSize���� �ݺ�
		if(2*i+1<=deapMaxSize){ // ���� �ڽ��� ���� ��
			if(deap[i*2]<deap[i*2+1]){ // �� �ڽİ��� ���Ͽ� �������� �θ𰪿� ����
				deap[i] = deap[i*2], i=i*2;
			}
			else{
				deap[i] = deap[i*2+1], i=i*2+1;
			}
		}
		else{ // ���� �ڽĸ� ������
			deap[i] = deap[i*2], i=i*2;
		}
	deap[i] = deap[deapMaxSize--]; // deapMaxSize�� ���δ�.
	return temp; 
}

int deleteMax(){  // deleteMin()�� ����
	int i, temp;
	if(deapMaxSize<2) printf("Error!!\n"), exit(0);
	else if(deapMaxSize==2) deleteMin(); // deapMaxSize==2�� MinHeap�� Root idx�̴�.
	else{
		temp = deap[3];  // MaxHeap�� Root�� idx�� 3�̴�.
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
	// Tree�� level�� sibling�� ������ŭ ���پ� ���
	for(i=2, j=4; i<=deapMaxSize; i++){
		if(i==j) printf("\n"), j*=2;  // sibling ��¿� ���� �������� �� sibling*2
		printf("%d  ", deap[i]);
	}
}

void printSortedOrder(){ // Heap, Deap Sort ���
	int i, j;
	int p, temp, heap[128];
	clock_t start, end;

	for(i=0; i<=deapMaxSize; i++) heap[i] = deap[i+1];  // Deap->Heap ����

	printf("====PRINT Sorted Order====\n");
	printf("[Using HeapSort]\n");

	start = clock(); // heap�� ���� start clock

	for(i=2; i<=deapMaxSize-1; i++)
	for(j=i; heap[j/2]<heap[j] && j>1; j/=2) SWAP(heap[j/2], heap[j], temp);
	//�θ�� �ڽİ��� ���ϸ鼭 MAX_Heap ����

	for(i=1; i<deapMaxSize-1; i++){
		SWAP(heap[1], heap[deapMaxSize-i], temp);  // Root <-> deapMaxSize-1�� ����
		for(j=1; j*2<deapMaxSize-1-i; ) // (deapMaxSize-1)-i ���Ĵ� ���ĵ������Ƿ�, �������� ����
			if(j*2+1<=deapMaxSize-1-i) // ����, ������ �ڽ��� ��� �����Ҷ�
				if(heap[j*2] > heap[j*2+1]) // ū ���� ã�� �ٽ� �ڽŰ� ���Ͽ� SWAP
					if(heap[j*2] > heap[j]) SWAP(heap[j], heap[j*2], temp), j*=2;
					else break;
				else
					if(heap[j*2+1] > heap[j]) SWAP(heap[j], heap[j*2+1], temp), j=j*2+1;
					else break;
			else // �����ڽĸ� ������
				if(heap[j*2] > heap[j]) SWAP(heap[j], heap[j*2], temp), j*=2;
	}

	for(i=1; i<deapMaxSize; i++) printf("%3d\n", heap[i]);
	end = clock();

	printf("Duration : %.3lf\n", (double)(end-start)/CLK_TCK);
	printf("[Using Deap's Deletion]\n");
	
	p=deapMaxSize;  // deleteMin()���� deapMaxSize�� -1 �ϹǷ� p�� �����ؼ� ���
	
	start = clock(); // deap�� ���� start clock
	for(i=2; i<=p; i++){
		printf("%3d\n", deleteMin());
	}
	end = clock();

	printf("Deap is empty\n");
	printf("Duration : %.3lf\n", (double)(end-start)/CLK_TCK);
}