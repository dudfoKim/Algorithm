#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>  // console size & clear ��� ���

//linked list, chainning, division
#define MAX_CHAR 50
#define TABLE_SIZE 13

typedef struct{
	char Key_Num[MAX_CHAR]; // ��ǰ�� ��ȣ
	char description[20]; // ��ǰ�� ����
	int stored_num; // ��ǰ�� ���
	int reorder_level; // ��ǰ�� ���ֹ� �ܰ�
}element;

typedef struct list *list_pointer;
typedef struct list{ // item & link�� ���� struct list ����
	element item;  
	list_pointer link;  
}List;

list_pointer hash_table[TABLE_SIZE];  // hash_table[13] 

void Init_table();  // Init & allocate hash_table[]
int hash(char *key);  // find key. (using mod x)
int transform(char *key);  // ASCII������ �� ���ڸ� ADD
void Insert(list_pointer pt);  // hash_table[key] ���� list ����
void Show(list_pointer pt);  // element ���
int search(char *key);  // key_Num[]�� ���� �˻�
void del(char *key);  // ����