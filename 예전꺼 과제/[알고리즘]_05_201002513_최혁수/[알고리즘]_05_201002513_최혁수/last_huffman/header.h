#include <stdio.h>
#include <stdlib.h>

#define Swap(x,y,t) ((t)=(x), (x)=(y), (y)=(t))  // macro : Swap function
// �ܾ� �Ѱ�(=Word)�� 1byte�� ǥ���ǰ� �̴� 8��Ʈ �̹Ƿ�, �� 256���� �����Ѵ�.
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
int getFrequency(int index); // (�Ǻ�) idx>0? freqArr[index] : huffmanTree.tree[-index].frequency
void initFrequencyArray();    // Init freqArr[]=0
int countFrequency(char* sourceFileName);  // counting the number of data(be repeated)
void initMinHeap();  // �����Ͱ� �����ϸ�, call insertMinheap() -> adjust() <=> MK Minheap
int deleteMinHeap();  // Minheap�� hArr[1]�� ���� ���������� ������. (adjust_delete()�� �� �籸��)
void insertMinHeap(int index);  // huffmanTree_node -> Minheap�� insert. (Minheap �籸��)
void adjust(int root, int n);  // �� �籸��
void adjust_delete();          // Minheap�� �籸���� ���� adjust()�� ����Ҽ� ���� �߰�����

void makeHuffmanTree();   // huffmanTree�� node�� �����, �̸� Minheap�� insert �Ѵ�.
int insertNodeToHuffmanTree(int left, int right);  // sum of Lef, Rig Frequency  && Lef, Rig �� �ʱ�ȭ
void initHuffmanCode();     // HuffmanCode()�� member ���� �ʱ�ȭ = 0
void generateHuffmanCode();  // MK HuffmanCode. (using traverseTree())
void traverseTree(int root, int bitLoc, char* tcode);  // Tree�� ��ȸ�ϸ鼭 ���� = 0, ������ = 1 �� huffmanCode ����
void printHuffmanCode();  // print

/*************** encoding && decoding function ******************/
void fileEncoder(char* sourceFile, char* targetFile, int sourceFileSize);
void encodingHuffTree(FILE* targetFile);  // �빮��(Hexa)�� ��� && ����? +FF : +00
void bitWriter(FILE* targetFile, char bit);  // ��Ʈ 1���� �Է¹޾� ���Ͽ� ����.
void initBitWriter();  // Init
void fileDecoder(char* originalFile, char* zipFile);  // Decoding = encoding�� �������� ����
void decodingHuffTree(FILE* zipFile);
char codeReader(FILE* zipFile);  // huffmanCode�� �д´�.
int bitReader(FILE* zipFile);  // 1bit Read -> return (from zipFile)

/*****************�� �� �� ��******************/
Heap heap;
HuffmanTree huffTree;
HuffmanCode huffCode[NUM_OF_CODES];
int freqArr[NUM_OF_CODES];

unsigned char writedbyte;
int bitCount;
