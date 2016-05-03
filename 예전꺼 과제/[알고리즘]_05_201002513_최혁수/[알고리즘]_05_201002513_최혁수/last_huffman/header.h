#include <stdio.h>
#include <stdlib.h>

#define Swap(x,y,t) ((t)=(x), (x)=(y), (y)=(t))  // macro : Swap function
// 단어 한개(=Word)는 1byte로 표현되고 이는 8비트 이므로, 총 256가지 존재한다.
#define NUM_OF_CODES 256  

typedef struct _Heap{
	int hArr[NUM_OF_CODES+1];  // index of heap
	int hSize; 
}Heap;

typedef struct _tree_node {
	int frequency;   // sum of two's data_frequency 
	short left;        // left or right data = idx
	short right;
} tree_node;

typedef struct _HuffmanTree{
	int tSize;                                  // size of Huffman Tree
	tree_node tree[NUM_OF_CODES];  // MK HuffmanTree
} HuffmanTree;

typedef struct _HuffmanCode{
	char code[NUM_OF_CODES];         // HuffmanCode
	unsigned char codeSize;
}HuffmanCode;

/*************************** MK minheap && huffmanTree_or_Code *****************************/
int getFrequency(int index); // (판별) idx>0? freqArr[index] : huffmanTree.tree[-index].frequency
void initFrequencyArray();    // Init freqArr[]=0
int countFrequency(char* sourceFileName);  // counting the number of data(be repeated)
void initMinHeap();  // 데이터가 존재하면, call insertMinheap() -> adjust() <=> MK Minheap
int deleteMinHeap();  // Minheap의 hArr[1]의 값을 순차적으로 빼낸다. (adjust_delete()로 힙 재구성)
void insertMinHeap(int index);  // huffmanTree_node -> Minheap에 insert. (Minheap 재구성)
void adjust(int root, int n);  // 힙 재구성
void adjust_delete();          // Minheap의 재구성은 기존 adjust()로 사용할수 없어 추가구현

void makeHuffmanTree();   // huffmanTree의 node를 만들고, 이를 Minheap에 insert 한다.
int insertNodeToHuffmanTree(int left, int right);  // sum of Lef, Rig Frequency  && Lef, Rig 값 초기화
void initHuffmanCode();     // HuffmanCode()의 member 변수 초기화 = 0
void generateHuffmanCode();  // MK HuffmanCode. (using traverseTree())
void traverseTree(int root, int bitLoc, char* tcode);  // Tree를 순회하면서 왼쪽 = 0, 오른쪽 = 1 로 huffmanCode 생성
void printHuffmanCode();  // print

/*************** encoding && decoding function ******************/
void fileEncoder(char* sourceFile, char* targetFile, int sourceFileSize);
void encodingHuffTree(FILE* targetFile);  // 대문자(Hexa)로 출력 && 음수? +FF : +00
void bitWriter(FILE* targetFile, char bit);  // 비트 1개를 입력받아 파일에 쓴다.
void initBitWriter();  // Init
void fileDecoder(char* originalFile, char* zipFile);  // Decoding = encoding을 역순으로 실행
void decodingHuffTree(FILE* zipFile);
char codeReader(FILE* zipFile);  // huffmanCode를 읽는다.
int bitReader(FILE* zipFile);  // 1bit Read -> return (from zipFile)

/*****************전 역 변 수******************/
Heap heap;
HuffmanTree huffTree;
HuffmanCode huffCode[NUM_OF_CODES];
int freqArr[NUM_OF_CODES];

unsigned char writedbyte;
int bitCount;
