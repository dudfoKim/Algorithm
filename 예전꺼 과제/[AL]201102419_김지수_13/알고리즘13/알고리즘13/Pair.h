#pragma once
#include "Global.h"
#include "Point.h"

typedef struct _Pair Pair;

struct _Pair 
{
	Point * point1;
	Point * point2;
};

Pair * Pair_new (Point * p1, Point * p2) ;
//�־��� �� ������ �����Ǵ� pair ��ü�� ����
void Pair_free (Pair * _this) ;
Distance Pair_distance (Pair * _this) ;
//������ �ִ� �� �� ������ �Ÿ��� ��´�.
Point * Pair_1stPoint (Pair * _this) ;
//Pair�� ù��° ���� ��´�.
Point * Pair_2ndPoint (Pair * _this) ;
//Pair�� �ι�° ���� ��´�.
void Pair_set1stPoint (Pair * _this, Point * p) ;
void Pair_set2ndPoint (Pair * _this, Point * p) ;
void Pair_show(Pair * _this, int indentCount, char * title) ;
//Debugging �뵵

