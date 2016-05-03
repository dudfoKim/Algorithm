#include "head.h"

void Init_table(){  // allocate & Init the hash_table[]
	int i;
	for(i=0; i<TABLE_SIZE; i++){
		hash_table[i] = (list_pointer)malloc(sizeof(struct list));
		hash_table[i]->link = NULL;
	}
}

int hash(char *key){  // find key. (mod)
	return (transform(key) % TABLE_SIZE);
}

int transform(char *key){  // ASCII �̿��Ͽ� �� ���� ����
	int number=0;
	while(*key) number += *key++;
	return number;
}
void Insert(list_pointer pt){  // hash_table[key] ���� list ����
	list_pointer first;
	list_pointer temp = (List *)malloc(sizeof(struct list));

	strcpy(temp->item.Key_Num, pt->item.Key_Num);
	strcpy(temp->item.description, pt->item.description);
	temp->item.reorder_level = pt->item.reorder_level;
	temp->item.stored_num = pt->item.stored_num;
	temp->link = NULL;

	first = hash_table[hash(temp->item.Key_Num)];
	while(first->link != NULL){  // NULL ���� ����
		first = first->link;
		Show(first);  // ���� element ���
	}
	first->link = temp;
	Show(temp);  // �Էµ� element ���
}

int search(char *key){

	list_pointer search_node = (list_pointer)malloc(sizeof(struct list));
	// hash_table[]�� ������ �˻�
	for(search_node=hash_table[hash(key)]; ; search_node = search_node->link){
		if(search_node==NULL){  // empty? break;
			break;
		}
		if(!strcmp(key, search_node->item.Key_Num)){  // key�� �����ϸ� ���
			Show(search_node); 
		}
	}
}


void Show(list_pointer pt){  // print the element
	printf("*************** print ******************\n");
	printf("Key_Num : %s\n", pt->item.Key_Num);
	printf("description : %s\n",pt->item.description);
	printf("stored_num : %d\n", pt->item.stored_num);
	printf("reorder_level : %d\n", pt->item.reorder_level);
}

void del(char *key){
	
	list_pointer search_node = (list_pointer)malloc(sizeof(struct list));
	list_pointer temp;
	// hash_table[] ������ �˻�
	for(search_node=hash_table[hash(key)]; ; search_node = search_node->link){
		if(!strcmp(key, search_node->link->item.Key_Num)){  // ���� ã����
			search_node->link = search_node->link->link;  // ���� link�� ���� link�� ����
			break;
		}
	}
}