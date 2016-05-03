#include "header.h"

int getFrequency(int index){  // 양수=freqArr[], 음수=huffTree.tree[].frequency
	if(index>0) return freqArr[index];
	else return huffTree.tree[-index].frequency;
}

void initFrequencyArray(){  // Init freqArr[]
	int i;
	for(i=0;  i<NUM_OF_CODES; i++) freqArr[i] = 0;
}

int countFrequency(char* sourceFileName){
	int check=0, i;  // check=sum of data
	char ch;
	FILE *file = fopen(sourceFileName,"r");  // read sourceFileName
	while(!feof(file)){
		fscanf(file, "%c", &ch);
		freqArr[ch]++, check++;  //store frequency
	}
	freqArr[ch]--;
	return check;
}

void initMinHeap(){
	int i;
	for(i=0; i<NUM_OF_CODES; i++)
		if(freqArr[i]!=0) insertMinHeap(i);  // data? insertMinHeap() : continue
}

void insertMinHeap(int index){
	//idx = (heap.hSize+1)에 data를 저장, adjust() = 힙 재정의
	heap.hArr[++heap.hSize] = index, adjust(1, heap.hSize);
}

void adjust(int root, int n){
	int i, temp;
	for(i=n;  i>root; i/=2)
		// if(parent > child), then Swap(parent, child)
		if(getFrequency(heap.hArr[i]) < getFrequency(heap.hArr[i/2]))
		Swap(heap.hArr[i/2], heap.hArr[i], temp);
}

void adjust_delete(){  // parent || sibling 순차비교하면서 최소힙 재구성
	int i=1, temp;
	while(i*2<=heap.hSize)
		if(i*2+1<=heap.hSize)
				if(getFrequency(heap.hArr[2*i]) < getFrequency(heap.hArr[2*i+1]))
					if(getFrequency(heap.hArr[i]) > getFrequency(heap.hArr[2*i])){
						Swap(heap.hArr[i], heap.hArr[2*i], temp), i*=2;
					}
					else break;
				else
				if(getFrequency(heap.hArr[i]) > getFrequency(heap.hArr[2*i+1])){
					Swap(heap.hArr[i], heap.hArr[2*i+1], temp), i=i*2+1;
				}
				else break;
		else
			if (getFrequency(heap.hArr[i]) > getFrequency(heap.hArr[2*i])){
				Swap(heap.hArr[i], heap.hArr[2*i], temp), i*=2;
			}
			else break;
}

int deleteMinHeap(){  // hArr[1] return && 최소힙 재구성
	int first = heap.hArr[1];
	heap.hArr[1] = heap.hArr[heap.hSize];
	heap.hArr[heap.hSize--] = 0;  // return시 데이터가 1개 삭제됬다는 의미로, hSize-=1
	adjust_delete();
	return first;
}

void makeHuffmanTree(){
	int one, two, index;
	while(heap.hSize>=2){  // 2개 데이터가 남을때까지 수행
		one = deleteMinHeap(), two = deleteMinHeap();  // 2개의 데이터를 pop하여, 각각 저장
		index = insertNodeToHuffmanTree(one, two);  // HuffmanTree 생성 및 return
		insertMinHeap(index);  // Minheap에 insert && 재구성
	}
}

int insertNodeToHuffmanTree(int left, int right){
	huffTree.tSize++;
	huffTree.tree[huffTree.tSize].frequency = getFrequency(left) + getFrequency(right);  // 두 frequency를 합
	huffTree.tree[huffTree.tSize].left = left;  //Lef & Rig 저장
	huffTree.tree[huffTree.tSize].right = right;
	return -huffTree.tSize;  // freq_idx 와 비교하기 위해 '-' 음수표현.  *판별가능 : getFrequency()
}

void initHuffmanCode(){  // Init
	int i=0, j=0;
	for(i; i<NUM_OF_CODES; i++){
		huffCode[i].codeSize = 0;
		for(j; j<NUM_OF_CODES; j++)
			huffCode[i].code[j] = 0;
	}
}

void generateHuffmanCode(){  // binary_code = temporary storages of huffman_code[]
	char binary_code[NUM_OF_CODES];
	traverseTree(-huffTree.tSize, 0, binary_code);  // 순회 = 허프만코드 발생
}

void traverseTree(int root, int bitLoc, char* binary_code){  // 순회시 왼쪽 = 0, 오른쪽 = 1 이진코드 저장
	int i;
	if(root >=0){ // LeafNode일 경우 저장된 code를 huffCode[].code[]에 저장
		for(i=0; i<bitLoc; i++)  huffCode[root].code[i] = binary_code[i]; 
		huffCode[root].codeSize = bitLoc;
	}
	else{
		binary_code[bitLoc] = '0';
		traverseTree(huffTree.tree[-root].left, bitLoc+1, binary_code);
		binary_code[bitLoc] = '1';
		traverseTree(huffTree.tree[-root].right, bitLoc+1, binary_code);
	}
}

void printHuffmanCode(){  // Print
	int i;
	for (i=0; i<NUM_OF_CODES; i++)
		if(freqArr[i]!=0) printf("%c[%d]: %s\n", i, i, huffCode[i].code);
}

