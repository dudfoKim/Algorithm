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
//주어진 두 점으로 구성되는 pair 객체를 생성
void Pair_free (Pair * _this) ;
Distance Pair_distance (Pair * _this) ;
//가지고 있는 두 점 사이의 거리를 얻는다.
Point * Pair_1stPoint (Pair * _this) ;
//Pair의 첫번째 점을 얻는다.
Point * Pair_2ndPoint (Pair * _this) ;
//Pair의 두번째 점을 얻는다.
void Pair_set1stPoint (Pair * _this, Point * p) ;
void Pair_set2ndPoint (Pair * _this, Point * p) ;
void Pair_show(Pair * _this, int indentCount, char * title) ;
//Debugging 용도

