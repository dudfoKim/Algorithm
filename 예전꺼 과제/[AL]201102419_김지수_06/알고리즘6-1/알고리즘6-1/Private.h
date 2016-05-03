#pragma once

#include "Global.h"

typedef struct _ArrayList ArrayList;

struct _ArrayList
{
	int maxLength ; // ����Ʈ�� �ִ� ����
	int length ; // ����Ʈ�� ���� (����� ������ ����)
	Element * body ; // ����Ʈ�� ���Ҹ� ������ �迭
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
