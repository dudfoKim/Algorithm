#pragma once
#include "Global.h"
#include "Point.h"

typedef struct _PointSet PointSet;

struct _PointSet 
{
	int maxSize ; // PointSet�� �ִ� ũ��
	int size ; // point �� ����
	Point ** body ; // point ��ü�� �迭
};

PointSet * PointSet_new (int givenMaxSize) ;
void PointSet_free (PointSet * _this) ;
Bool PointSet_isEmpty (PointSet * _this) ;
Bool PointSet_isFull (PointSet * _this) ;
int PointSet_size (PointSet * _this) ;
Bool PointSet_isPointIndexOK (PointSet * _this, PointIndex index) ;
Point * PointSet_kthPoint (PointSet * _this, PointIndex index) ;
Bool PointSet_addPoint (PointSet * _this, Point * p) ;
Point * PointSet_pointAtIndex (PointSet * _this, PointIndex index);
