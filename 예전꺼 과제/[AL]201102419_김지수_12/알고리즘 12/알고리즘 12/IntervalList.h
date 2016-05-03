#pragma once
#include "Global.h"

typedef struct _IntervalList IntervalList;
typedef struct _Node Node ;

struct _IntervalList
{
	int length ; // list�� ����ִ� ����� ����
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