#pragma once
#include "Global.h"

typedef struct _IntervalList IntervalList;
typedef struct _Node Node ;

struct _IntervalList
{
	int length ; // list에 들어있는 노드의 개수
	Node * head ;
};

struct _Node 
{
	int e ;
	Node * next ;
};

IntervalList * IntervalList_new ();
void IntervalList_free (IntervalList * _this);
void IntervalList_add (IntervalList * _this, int input);