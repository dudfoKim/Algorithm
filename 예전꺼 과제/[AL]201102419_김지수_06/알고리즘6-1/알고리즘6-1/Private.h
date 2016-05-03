#pragma once

#include "Global.h"

typedef struct _ArrayList ArrayList;

struct _ArrayList
{
	int maxLength ; // 리스트의 최대 길이
	int length ; // 리스트의 길이 (저장된 원소의 개수)
	Element * body ; // 리스트의 원소를 저장할 배열
};

typedef struct _ArrayListIter ArrayListIter;

struct _ArrayListIter
{
	ArrayList * list ;
	int curLoc ;
};

typedef struct _IndexList IndexList;

struct _IndexList
{
	ArrayList * list;
	int * index;
};

typedef struct _IndexListIter IndexListIter;

struct _IndexListIter
{
	IndexList * indexList ;
	int curLoc ;
};
