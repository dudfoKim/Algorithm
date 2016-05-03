#pragma once

#include "Global.h"
#include "List.h"
#include "App.h"

typedef struct _Iterator Iterator;

struct _Iterator
{
	List * list ; // 검색해야 할 리스트
	Node * currentLocation ; //현재 (노드) 위치
};

Iterator* Iterator_new(List * list);
void Iterator_free (Iterator * _this);
void Iterator_begin (Iterator * _this);
Bool Iterator_endOfList (Iterator * _this);
Element Iterator_currentElement (Iterator * _this);
void Iterator_next (Iterator * _this);