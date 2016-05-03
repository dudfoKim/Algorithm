#include "header.h"

/*************** encoding function ******************/
void fileEncoder(char* sourceFile, char* targetFile, int sourceFileSize){
	FILE* open_file = fopen(sourceFile, "r");  // Read || Write
	FILE* store_file = fopen(targetFile, "w");
	int i, size;
	char c;
	encodingHuffTree(store_file);
	fseek(open_file, 0, SEEK_END);  // find destination. (cuz -0bit)
	size = ftell(open_file);
	fseek(open_file, 0, SEEK_SET);  // find starting point. (cuz + 0bit)

	fprintf(store_file, "%08X ", size);

	while(fscanf(open_file, "%c", &c) != EOF)  // 1bit ������ �޾�, ������ ���������� bitWriter() ����
		for(i=0; huffCode[c].code[i]!='\0'; i++) bitWriter(store_file, huffCode[c].code[i]);
	// bitCount!=0 : 8bit ������ ���� ���Ͽ��ٴ� ������, ������ bit��ŭ ���� �Է�
	if(bitCount!=0) fprintf(store_file, "%02X ", writedbyte << (8-bitCount) & (0x80>>bitCount) );
}

void encodingHuffTree(FILE* targetFile){  // (huffTree.tree[].left or right) ����? +FF : +00
	int i;
	fprintf(targetFile, "%02X ", huffTree.tSize);
	for (i=1; i<=huffTree.tSize; i++){
		fprintf(targetFile, "%02X ", huffTree.tree[i].left & 0x000000FF);  // 0x000000FF : 1byte Masking
		if ( huffTree.tree[i].left > -1 ) fprintf(targetFile, "00 ");
		else fprintf(targetFile, "FF ");

		fprintf(targetFile, "%02X ", huffTree.tree[i].right & 0x000000FF);
		if ( huffTree.tree[i].right > -1 ) fprintf(targetFile, "00 ");
		else fprintf(targetFile, "FF ");
	}
}

void bitWriter(FILE* targetFile, char bit){  // 1bit ������ �޾�, write �Ѵ�.
	bitCount++;
	writedbyte = writedbyte << 1 | (bit-48);
	if(bitCount==8){  // 8bit ������ ������ Init
		bitCount = 0;
		//�ǽ�PDF ���Ͽ� ���õ� �ڵ�����, �̷� ������ �ùٸ��� ���� En&Decoding ����. (but, no Error)
		//fputc(writedbyte, targetFile);/
		fprintf(targetFile, "%02X ", writedbyte);
	}
}

void initBitWriter(){  // Init
	bitCount = 0, writedbyte = 0;
}

/*************** decoding function ******************/
void fileDecoder(char* originalFile, char* zipFile){
	FILE* open_file = fopen(zipFile, "r");
	FILE* store_file = fopen(originalFile, "w");
	int i, size;

	initBitWriter();
	decodingHuffTree(open_file);
	fscanf(open_file, "%X", &size);
	// Read data(open_file), Write data.(store_file)
	for(i=0; i<size; i++) fprintf(store_file,"%c",codeReader(open_file));
}

void decodingHuffTree(FILE* zipFile){
	int i, temp;
	fscanf(zipFile, "%X", &huffTree.tSize); // huffTree.tSize�� number�� Read->Store

	for(i=1; i<=huffTree.tSize; i++){
		fscanf(zipFile, "%X", &huffTree.tree[i].left);  // 1st, 2nd Data Read -> Sum
		fscanf(zipFile, "%X", &temp);
		// 0xFF00 masking�� �̿� �����͸� ��ģ��.
		huffTree.tree[i].left = huffTree.tree[i].left | ( temp << 8 & 0xff00 );

		fscanf(zipFile, "%X", &huffTree.tree[i].right);
		fscanf(zipFile, "%X", &temp);
		huffTree.tree[i].right = huffTree.tree[i].right | ( temp << 8 & 0xff00 );
	}
}

char codeReader(FILE* zipFile){
	int node, way;
	for(node=-huffTree.tSize; node<0;){
		way = bitReader(zipFile);  // �����б�
		if(way == 0) node = huffTree.tree[-node].left;  // ���ڰ� 0�̸� ����, else ������
		else node = huffTree.tree[-node].right;
	}

	return node;
}

int bitReader(FILE* zipFile){
	int first;
	if (bitCount%8==0){  // 8bit�� ���� write �Ͽ�����
		fscanf(zipFile, "%X", &writedbyte);  // ���� �����͸� �����´�.
		bitCount = 0;
	}
	first = (writedbyte >> 7-bitCount) & 1;  // �� bit�� ä��� ���ڸ��� first�� ����
	bitCount++;
	return first;
}