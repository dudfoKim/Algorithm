#include "header.h"

int main()
{
	char originalFileName[20];
	char zipFileName[20];
	int fileSize;
	char command;
	printf("[e]���� [d]�������� \n Select Menu > ");
	scanf("%c", &command);
	if(command == 'e')
	{
		printf("������ ���� �̸��� �Է��Ͻÿ� > ");
		scanf("%s",originalFileName);
		printf("������ �������� �̸��� �Է��Ͻÿ�> ");
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
		printf("����Ǯ ���� �̸��� �Է��Ͻÿ� > ");
		scanf("%s",zipFileName);
		printf("������ Ǯ�� ������ ���� �̸��� �Է��Ͻÿ� > ");
		scanf("%s",originalFileName);
		fileDecoder(originalFileName, zipFileName);
	}
	return 0;
}