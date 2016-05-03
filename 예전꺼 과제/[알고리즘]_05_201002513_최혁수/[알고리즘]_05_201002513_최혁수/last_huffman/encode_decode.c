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

	while(fscanf(open_file, "%c", &c) != EOF)  // 1bit 정보를 받아, 파일이 끝날때까지 bitWriter() 수행
		for(i=0; huffCode[c].code[i]!='\0'; i++) bitWriter(store_file, huffCode[c].code[i]);
	// bitCount!=0 : 8bit 정보를 받지 못하였다는 것으로, 나머지 bit만큼 정보 입력
	if(bitCount!=0) fprintf(store_file, "%02X ", writedbyte << (8-bitCount) & (0x80>>bitCount) );
}

void encodingHuffTree(FILE* targetFile){  // (huffTree.tree[].left or right) 음수? +FF : +00
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

void bitWriter(FILE* targetFile, char bit){  // 1bit 정보를 받아, write 한다.
	bitCount++;
	writedbyte = writedbyte << 1 | (bit-48);
	if(bitCount==8){  // 8bit 정보를 받으면 Init
		bitCount = 0;
		//실습PDF 파일에 제시된 코드지만, 이로 받으면 올바르지 않은 En&Decoding 수행. (but, no Error)
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
	fscanf(zipFile, "%X", &huffTree.tSize); // huffTree.tSize에 number를 Read->Store

	for(i=1; i<=huffTree.tSize; i++){
		fscanf(zipFile, "%X", &huffTree.tree[i].left);  // 1st, 2nd Data Read -> Sum
		fscanf(zipFile, "%X", &temp);
		// 0xFF00 masking을 이용 데이터를 합친다.
		huffTree.tree[i].left = huffTree.tree[i].left | ( temp << 8 & 0xff00 );

		fscanf(zipFile, "%X", &huffTree.tree[i].right);
		fscanf(zipFile, "%X", &temp);
		huffTree.tree[i].right = huffTree.tree[i].right | ( temp << 8 & 0xff00 );
	}
}

char codeReader(FILE* zipFile){
	int node, way;
	for(node=-huffTree.tSize; node<0;){
		way = bitReader(zipFile);  // 문자읽기
		if(way == 0) node = huffTree.tree[-node].left;  // 문자가 0이면 왼쪽, else 오른쪽
		else node = huffTree.tree[-node].right;
	}

	return node;
}

int bitReader(FILE* zipFile){
	int first;
	if (bitCount%8==0){  // 8bit를 전부 write 하였으면
		fscanf(zipFile, "%X", &writedbyte);  // 새로 데이터를 가져온다.
		bitCount = 0;
	}
	first = (writedbyte >> 7-bitCount) & 1;  // 빈 bit를 채우고 끝자리를 first에 저장
	bitCount++;
	return first;
}