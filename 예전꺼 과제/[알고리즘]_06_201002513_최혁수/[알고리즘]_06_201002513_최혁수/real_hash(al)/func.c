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

int transform(char *key){  // ASCII 이용하여 각 문자 덧셈
	int number=0;
	while(*key) number += *key++;
	return number;
}
void Insert(list_pointer pt){  // hash_table[key] 끝에 list 삽입
	list_pointer first;
	list_pointer temp = (List *)malloc(sizeof(struct list));

	strcpy(temp->item.Key_Num, pt->item.Key_Num);
	strcpy(temp->item.description, pt->item.description);
	temp->item.reorder_level = pt->item.reorder_level;
	temp->item.stored_num = pt->item.stored_num;
	temp->link = NULL;

	first = hash_table[hash(temp->item.Key_Num)];
	while(first->link != NULL){  // NULL 까지 수행
		first = first->link;
		Show(first);  // 기존 element 출력
	}
	first->link = temp;
	Show(temp);  // 입력된 element 출력
}

int search(char *key){

	list_pointer search_node = (list_pointer)malloc(sizeof(struct list));
	// hash_table[]의 끝까지 검색
	for(search_node=hash_table[hash(key)]; ; search_node = search_node->link){
		if(search_node==NULL){  // empty? break;
			break;
		}
		if(!strcmp(key, search_node->item.Key_Num)){  // key와 동일하면 출력
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
	// hash_table[] 끝까지 검색
	for(search_node=hash_table[hash(key)]; ; search_node = search_node->link){
		if(!strcmp(key, search_node->link->item.Key_Num)){  // 값을 찾으면
			search_node->link = search_node->link->link;  // 이전 link와 다음 link를 연결
			break;
		}
	}
}