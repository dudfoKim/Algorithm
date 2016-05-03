#pragma once
#include "Global.h"


typedef struct _LinkedList LinkedList;
typedef struct _Node Node ;

struct _LinkedList
{
	int length ; // list에 들어있는 노드의 개수
	Node * head ;
	Node * rear;
} ;


struct _Node 
{
	Person e ;
	Node * next ;
} ;
//Role
//Edge Node로 구성되는 리스트이다.
//Coloring_checkColors()에서, edge의 양끝 vertex의 color가 같은 edge들을 모아 놓는데 사용한다.
//Public functions
LinkedList * LinkedList_new () ;
void LinkedList_free (LinkedList * _this) ;
Bool LinkedList_isEmpty (LinkedList * _this) ;
Bool LinkedList_isFull (LinkedList * _this) ;
void LinkedList_add (LinkedList * _this, Person e) ;
int LinkedList_delete(LinkedList * _this);