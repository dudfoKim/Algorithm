#pragma once
#include "Global.h"
#include "IntervalList.h"

typedef struct _ListIterator ListIterator;

struct _ListIterator
{
	IntervalList * list ; // �˻��ؾ� �� ����Ʈ
	Node * currentLocation ; //���� (���) ��ġ
};

ListIterator * ListIterator_new (IntervalList * list);
void ListIterator_free (ListIterator * _this);
void ListIterator_begin (ListIterator * _this);
Bool ListIterator_end (ListIterator * _this);
int ListIterator_currentElement (ListIterator * _this);
void ListIterator_next (ListIterator * _this);