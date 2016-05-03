#pragma once

#include "Global.h"
#include "List.h"
#include "App.h"

typedef struct _Iterator Iterator;

struct _Iterator
{
	List * list ; // �˻��ؾ� �� ����Ʈ
	Node * currentLocation ; //���� (���) ��ġ
};

Iterator* Iterator_new(List * list);
void Iterator_free (Iterator * _this);
void Iterator_begin (Iterator * _this);
Bool Iterator_endOfList (Iterator * _this);
Element Iterator_currentElement (Iterator * _this);
void Iterator_next (Iterator * _this);