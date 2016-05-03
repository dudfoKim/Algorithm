#pragma once
#include "Global.h"
#include "PointSet.h"

typedef struct _PointIndexList PointIndexList;

struct _PointIndexList
{
	int maxSize ;
	int size ;
	PointSet * points ; // �����ϴ� ������ �ӽ� ������
	PointIndex * body ; // array of PointIndex
};

PointIndexList * PointIndexList_new (PointSet * points, int givenMaxSize) ;
//PointIndexList * PointIndexList_new2 (int givenMaxSize, PointSet * points);
//�⺻ ������  �ִ� ũ�Ⱑ �־�����.
//������ �� �����ڿ����� ����Ѵ�.
PointIndexList * PointIndexList_newBySortingX (PointSet * points) ;
//points�� point���� X ��ǥ�� ���ĵ� �ε��� ����Ʈ�� ����
PointIndexList * PointIndexList_newBySortingY (PointSet * points) ;
//points�� point���� Y ��ǥ�� ���ĵ� �ε��� ����Ʈ�� ����
void PointIndexList_free (PointIndexList * _this) ;
int PointIndexList_size (PointIndexList * _this) ;
PointIndex PointIndexList_pointIndex (PointIndexList * _this, int indexListLoc) ;
//PointIndexList�� indexListLoc ��° ��, �� PointSet ���� ���� ��ġ index�� ��´�.
Bool PointIndexList_add (PointIndexList * _this, PointIndex anIndex) ;
//�־��� PointIndex anIndex�� PointIndexList �� �߰��Ѵ�.
void PointIndexList_showPoints(PointIndexList * _this, int indentCount, char * title) ;
//Debugging �뵵
void PointIndexList_qsortByX (PointIndexList * _this);
void PointIndexList_qsortByY (PointIndexList * _this);
void PointIndexList_qsortByXRecursively (PointIndexList * _this, int left, int right);
void PointIndexList_qsortByYRecursively (PointIndexList * _this, int left, int right);
int PointIndexList_partitionByX(PointIndexList * _this, int left, int right);
int PointIndexList_partitionByY(PointIndexList * _this, int left, int right);
void PointIndexList_swap (PointIndexList * _this, int i, int j);