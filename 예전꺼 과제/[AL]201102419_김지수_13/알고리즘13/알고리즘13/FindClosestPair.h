#pragma once
#include "Global.h"
#include "PointSet.h"
#include "Pair.h"
#include "PointIndexList.h"

typedef struct _PointIndexListPair PointIndexListPair;

struct _PointIndexListPair
{
	PointIndexList * left ;
	PointIndexList * right ;
};

typedef struct _FindClosestPair FindClosestPair;

struct _FindClosestPair 
{
	PointSet * points ;
	// read-only 객체
	// 이 객체의 소멸은 FindClosestPair에서 책임지지 않는다
	int recursionDepth ; // only for debugging
} ;

typedef struct _SeparationLine SeparationLine;

struct _SeparationLine
{
	PointIndex midIndex ;
	Coordinate midX ;
};


FindClosestPair * FindClosestPair_new (PointSet * givenPoints);
void FindClosestPair_free (FindClosestPair * _this);
Pair * FindClosestPair_run (FindClosestPair * _this);


