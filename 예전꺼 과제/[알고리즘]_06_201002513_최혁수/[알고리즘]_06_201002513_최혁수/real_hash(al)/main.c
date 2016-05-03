#include "head.h"

int main(){
	list_pointer temp = (List*)malloc(sizeof(struct list));
	int i=1;
	system("mode con cols=41 lines=30");  // console size Á¶Àý
	Init_table();  // Init & allocate
	while(i!=4){
	printf("            select the option           \n");
	printf("****************************************\n");
	printf("1.input  2.search  3.delete  4.prog exit\n");
	printf("****************************************\n");
	printf("function : ");
	scanf("%d", &i);
	system("cls");  // console Clear
	switch(i){
	case 1:  // Input function
		printf("*************** input ******************\n");
		printf("Key_Num : ");
		scanf("%s", &temp->item.Key_Num);
		printf("Description : ");
		scanf("%s", &temp->item.description);
		printf("stored_num : ");
		scanf("%d", &temp->item.stored_num);
		printf("reorder_level : ");
		scanf("%d", &temp->item.reorder_level);
		system("cls");
		Insert(temp);
		break;
	case 2:  // Search function
		printf("Key_Num : ");
		scanf("%s", &temp->item.Key_Num);
		search(temp->item.Key_Num, i);
		break;
	case 3:  // Delete function
		printf("Key_Num : ");
		scanf("%s", &temp->item.Key_Num);
		del(temp->item.Key_Num);
		break;
	case 4:  // End of program(while)
		break;
	}
	}
}