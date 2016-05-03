#include "head.h"

int main(void)
{
	int temp;
	char select;

	printf("[i]Insert [d]Delete Min [D]Delete Max [p]Print [s]printSortedOrder [!]quit\n");
	while(1){
		printf(">> ");
		scanf("%c", &select);
		switch(select){
		case 'i' :
			scanf("%d", &temp);
			Insert(temp);
			break;
		case 'd' :
			printf("%5d\n", deleteMin());
			break;
		case 'D' :
			printf("%5d\n", deleteMax());
			break;
		case 'p' :
			print();
			printf("\n");
			break;
		case 's' :
			printSortedOrder();
			break;
		case '!':
			return 0;
		}
		fflush(stdin);
	}
}