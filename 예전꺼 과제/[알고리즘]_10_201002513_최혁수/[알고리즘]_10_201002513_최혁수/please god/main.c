#include <stdio.h>
#include <stdlib.h>
#include "23tree.h"
        
int main(int argc, char* argv[])
{
        int i = 0;
		char select;
		int insert;
        tree23* tree = makeTree23();
		while(1){
		printf("[i]Insert [d]Delete [p]Print [f]Find [q]quit\n");
		printf("Select : ");
		scanf("%c", &select);
		fflush(stdin);
		
		switch(select){
		case 'i':
			printf("Input : ");
			scanf("%d", &insert);
			fflush(stdin);
			insert23(tree, insert);
			break;
		case 'd':
			printf("Delete : ");
			scanf("%d", &insert);
			fflush(stdin);
			delete23(tree, insert);
			break;
		case 'p':
			printf("***** Print *****\n");
			print23(tree);
			printf("\n");
			break;
		case 'f':
			printf("Find : ");
			scanf("%d", &insert);
			fflush(stdin);
			if(search23(tree->root, insert))
				printf("Exist : %d \n", insert);
			else
				printf("Not Exist\n");
			break;
		case 'q':
			return 0;
		}
		}
}