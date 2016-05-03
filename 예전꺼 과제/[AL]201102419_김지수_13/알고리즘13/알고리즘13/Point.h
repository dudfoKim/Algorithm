#pragma once
#include "Global.h"

typedef struct _Point Point;

struct _Point 
{
	Coordinate x ;
	Coordinate y ;
} ;

Point * Point_new (void) ;
//Point 객체를 생성하는 기본 생성자
Point * Point_newWithXYCoordinates (Coordinate x, Coordinate y) ;
//주어진 (X,Y) 좌표로 구성되는 점 객체를 생성하는 생성자
void Point_free (Point * _this) ;
//소멸자
Coordinate Point_xCoordinate (Point * _this) ;
//점 객체의 X 좌표값을 얻는다
void Point_setXCoordinate (Point * _this, Coordinate x) ;
//점 객체의 X 좌표값을 지정
Coordinate Point_yCoordinate (Point * _this) ;
//점 객체의 Y 좌표값을 얻는다
void Point_setYCoordinate (Point * _this, Coordinate y) ;
//점 객체의 Y 좌표값을 지정
Distance Point_distanceTo (Point * _this, Point * givenPoint) ;
//현재의 점 _this에서 주어진 점 givenPoint까지의 Euclidean distance를 얻는다

