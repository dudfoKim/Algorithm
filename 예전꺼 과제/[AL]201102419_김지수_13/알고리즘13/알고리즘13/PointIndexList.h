#pragma once
#include "Global.h"
#include "PointSet.h"

typedef struct _PointIndexList PointIndexList;

struct _PointIndexList
{
	int maxSize ;
	int size ;
	PointSet * points ; // 정렬하는 동안의 임시 보관소
	PointIndex * body ; // array of PointIndex
};

PointIndexList * PointIndexList_new (PointSet * points, int givenMaxSize) ;
//PointIndexList * PointIndexList_new2 (int givenMaxSize, PointSet * points);
//기본 생성자  최대 크기가 주어진다.
//다음의 두 생성자에서도 사용한다.
PointIndexList * PointIndexList_newBySortingX (PointSet * points) ;
//points의 point들이 X 좌표로 정렬된 인덱스 리스트를 생성
PointIndexList * PointIndexList_newBySortingY (PointSet * points) ;
//points의 point들이 Y 좌표로 정렬된 인덱스 리스트를 생성
void PointIndexList_free (PointIndexList * _this) ;
int PointIndexList_size (PointIndexList * _this) ;
PointIndex PointIndexList_pointIndex (PointIndexList * _this, int indexListLoc) ;
//PointIndexList의 indexListLoc 번째 값, 즉 PointSet 상의 점의 위치 index를 얻는다.
Bool PointIndexList_add (PointIndexList * _this, PointIndex anIndex) ;
//주어진 PointIndex anIndex를 PointIndexList 에 추가한다.
void PointIndexList_showPoints(PointIndexList * _this, int indentCount, char * title) ;
//Debugging 용도
void PointIndexList_qsortByX (PointIndexList * _this);
void PointIndexList_qsortByY (PointIndexList * _this);
void PointIndexList_qsortByXRecursively (PointIndexList * _this, int left, int right);
void PointIndexList_qsortByYRecursively (PointIndexList * _this, int left, int right);
int PointIndexList_partitionByX(PointIndexList * _this, int left, int right);
int PointIndexList_partitionByY(PointIndexList * _this, int left, int right);
void PointIndexList_swap (PointIndexList * _this, int i, int j);