#pragma once
#include "Global.h"

typedef struct _Point Point;

struct _Point 
{
	Coordinate x ;
	Coordinate y ;
} ;

Point * Point_new (void) ;
//Point ��ü�� �����ϴ� �⺻ ������
Point * Point_newWithXYCoordinates (Coordinate x, Coordinate y) ;
//�־��� (X,Y) ��ǥ�� �����Ǵ� �� ��ü�� �����ϴ� ������
void Point_free (Point * _this) ;
//�Ҹ���
Coordinate Point_xCoordinate (Point * _this) ;
//�� ��ü�� X ��ǥ���� ��´�
void Point_setXCoordinate (Point * _this, Coordinate x) ;
//�� ��ü�� X ��ǥ���� ����
Coordinate Point_yCoordinate (Point * _this) ;
//�� ��ü�� Y ��ǥ���� ��´�
void Point_setYCoordinate (Point * _this, Coordinate y) ;
//�� ��ü�� Y ��ǥ���� ����
Distance Point_distanceTo (Point * _this, Point * givenPoint) ;
//������ �� _this���� �־��� �� givenPoint������ Euclidean distance�� ��´�

