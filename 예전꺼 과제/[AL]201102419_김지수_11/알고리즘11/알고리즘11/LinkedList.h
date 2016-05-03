#pragma once
#include "Global.h"


typedef struct _LinkedList LinkedList;
typedef struct _Node Node ;

struct _LinkedList
{
	int length ; // list�� ����ִ� ����� ����
	Node * head ;
	Node * rear;
} ;


struct _Node 
{
	Person e ;
	Node * next ;
} ;
//Role
//Edge Node�� �����Ǵ� ����Ʈ�̴�.
//Coloring_checkColors()����, edge�� �糡 vertex�� color�� ���� edge���� ��� ���µ� ����Ѵ�.
//Public functions
LinkedList * LinkedList_new () ;
void LinkedList_free (LinkedList * _this) ;
Bool LinkedList_isEmpty (LinkedList * _this) ;
Bool LinkedList_isFull (LinkedList * _this) ;
void LinkedList_add (LinkedList * _this, Person e) ;
int LinkedList_delete(LinkedList * _this);