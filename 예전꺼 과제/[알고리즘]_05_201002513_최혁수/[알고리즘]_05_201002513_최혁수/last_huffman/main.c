#include "header.h"

int main()
{
	char originalFileName[20];
	char zipFileName[20];
	int fileSize;
	char command;
	printf("[e]압축 [d]압축해제 \n Select Menu > ");
	scanf("%c", &command);
	if(command == 'e')
	{
		printf("압축할 파일 이름을 입력하시오 > ");
		scanf("%s",originalFileName);
		printf("저장할 압축파일 이름을 입력하시오> ");
		scanf("%s",zipFileName);
		initFrequencyArray();
		fileSize = countFrequency(originalFileName);
		initMinHeap();
		makeHuffmanTree();
		generateHuffmanCode();
		printHuffmanCode();
		fileEncoder(originalFileName, zipFileName, fileSize);
	}
	else
	{
		printf("압축풀 파일 이름을 입력하시오 > ");
		scanf("%s",zipFileName);
		printf("압축을 풀어 저장할 파일 이름을 입력하시오 > ");
		scanf("%s",originalFileName);
		fileDecoder(originalFileName, zipFileName);
	}
	return 0;
}