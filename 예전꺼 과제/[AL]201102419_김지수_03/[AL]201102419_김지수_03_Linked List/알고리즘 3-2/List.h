#pragma once
#include "Global.h"

typedef struct _Node Node;
typedef struct _List List;


struct _Node 
{
	Element item ;
	Node * next ;
};

struct _List 
{
	int length ; // 리스트에 들어 있는 원소의 개수
	Node * head ; // 원소들의 연결 리스트의 시작 주소
};

List * List_new (int maxSize);
void List_free (List * _this);
void List_reset(List* _this);
Bool List_isEmpty (List * _this);
Bool List_isFull (List * _this);
Bool List_isIndexOK(List* _this, int index);
Bool List_doesExist(List* _this, int element);
int List_length(List* _this);
void List_insert (List * _this, Element e);
Element List_deleteKth (List * _this, int K);
Element List_deleteMax (List * _this);
Element List_deleteMin (List * _this);
