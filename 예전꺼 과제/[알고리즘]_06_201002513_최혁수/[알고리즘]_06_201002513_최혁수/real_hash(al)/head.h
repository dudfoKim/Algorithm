#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>  // console size & clear 기능 사용

//linked list, chainning, division
#define MAX_CHAR 50
#define TABLE_SIZE 13

typedef struct{
	char Key_Num[MAX_CHAR]; // 제품의 번호
	char description[20]; // 제품의 설명
	int stored_num; // 제품의 재고량
	int reorder_level; // 제품의 재주문 단계
}element;

typedef struct list *list_pointer;
typedef struct list{ // item & link를 가진 struct list 선언
	element item;  
	list_pointer link;  
}List;

list_pointer hash_table[TABLE_SIZE];  // hash_table[13] 

void Init_table();  // Init & allocate hash_table[]
int hash(char *key);  // find key. (using mod x)
int transform(char *key);  // ASCII값으로 각 문자를 ADD
void Insert(list_pointer pt);  // hash_table[key] 끝에 list 삽입
void Show(list_pointer pt);  // element 출력
int search(char *key);  // key_Num[]에 따른 검색
void del(char *key);  // 삭제