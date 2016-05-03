#include "binary_header.h"
#include "binary_header2.h"

int main(void)
{
	char input;
	char select;
	BTreeNode * avlRoot;
	BSTInit(&avlRoot);
	while(1){
		fflush(stdin);
		printf("[i]Insert [s]Search [d]Delete [p]Print [q]quit\n");
		scanf("%c", &select);
		fflush(stdin);
		switch(select){
		case 'i':
			while(1){
			printf("Input the String you want : <To quit enter the 'q'>\n");
			printf("Input: ");
			scanf("%c", &input);
			if(input == 'q') break;
			fflush(stdin);
			BSTInsert(&avlRoot, input);
			BSTShow(avlRoot);
			printf("\n\n");
			}
			break;
		case 's':
			while(1){
			printf("Search data : <to quit enter the 'q'>\n");
			printf("Search: ");
			scanf("%c", &input);
			if(input == 'q') break;
			fflush(stdin);
			BSTShow(BSTSearch(avlRoot, input));
			printf("\n\n");
			}
			break;
		case 'd':
			while(1){
			printf("Delete data : <to quit enter the 'q'>\n");
			printf("Delete: ");
			scanf("%c", &input);
			if(input == 'q') break;
			fflush(stdin);
			BSTRemove(&avlRoot, input);
			printf("\n\n");
			}
			break;
		case 'p':
			if(avlRoot != NULL){
				printf("**********Inorder traversal of Tree**********\n");
				BSTShow(avlRoot);
			}
			else printf("[Error] Tree is empty!!");
			printf("\n\n");
			break;
		case 'q':
			return ;
		}
	}
}