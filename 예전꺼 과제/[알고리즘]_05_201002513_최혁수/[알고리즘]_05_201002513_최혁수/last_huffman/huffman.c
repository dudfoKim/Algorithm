#include "header.h"

int getFrequency(int index){  // ���=freqArr[], ����=huffTree.tree[].frequency
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
	//idx = (heap.hSize+1)�� data�� ����, adjust() = �� ������
	heap.hArr[++heap.hSize] = index, adjust(1, heap.hSize);
}

void adjust(int root, int n){
	int i, temp;
	for(i=n;  i>root; i/=2)
		// if(parent > child), then Swap(parent, child)
		if(getFrequency(heap.hArr[i]) < getFrequency(heap.hArr[i/2]))
		Swap(heap.hArr[i/2], heap.hArr[i], temp);
}

void adjust_delete(){  // parent || sibling �������ϸ鼭 �ּ��� �籸��
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

int deleteMinHeap(){  // hArr[1] return && �ּ��� �籸��
	int first = heap.hArr[1];
	heap.hArr[1] = heap.hArr[heap.hSize];
	heap.hArr[heap.hSize--] = 0;  // return�� �����Ͱ� 1�� ������ٴ� �ǹ̷�, hSize-=1
	adjust_delete();
	return first;
}

void makeHuffmanTree(){
	int one, two, index;
	while(heap.hSize>=2){  // 2�� �����Ͱ� ���������� ����
		one = deleteMinHeap(), two = deleteMinHeap();  // 2���� �����͸� pop�Ͽ�, ���� ����
		index = insertNodeToHuffmanTree(one, two);  // HuffmanTree ���� �� return
		insertMinHeap(index);  // Minheap�� insert && �籸��
	}
}

int insertNodeToHuffmanTree(int left, int right){
	huffTree.tSize++;
	huffTree.tree[huffTree.tSize].frequency = getFrequency(left) + getFrequency(right);  // �� frequency�� ��
	huffTree.tree[huffTree.tSize].left = left;  //Lef & Rig ����
	huffTree.tree[huffTree.tSize].right = right;
	return -huffTree.tSize;  // freq_idx �� ���ϱ� ���� '-' ����ǥ��.  *�Ǻ����� : getFrequency()
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
	traverseTree(-huffTree.tSize, 0, binary_code);  // ��ȸ = �������ڵ� �߻�
}

void traverseTree(int root, int bitLoc, char* binary_code){  // ��ȸ�� ���� = 0, ������ = 1 �����ڵ� ����
	int i;
	if(root >=0){ // LeafNode�� ��� ����� code�� huffCode[].code[]�� ����
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

