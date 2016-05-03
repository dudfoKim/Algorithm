#include "Point.h"

Point * Point_new (void)
{
	Point * _this = NewObject(Point) ;

	return _this ;
}

Point * Point_newWithXYCoordinates (Coordinate givenX, Coordinate givenY)
{
	Point * _this = Point_new() ;
	_this->x = givenX ;
	_this->y = givenY ;

	return _this ;
}

void Point_free (Point * _this)
{
	free(_this) ;
}

Coordinate Point_xCoordinate (Point * _this)
{
	return _this->x ;
}

void Point_setXCoordinate (Point * _this, Coordinate givenX)
{
	_this->x = givenX ;
}

Coordinate Point_yCoordinate (Point * _this)
{
	return _this->y;
	// ���⸦ ä��ÿ�
}

void Point_setYCoordinate (Point * _this, Coordinate givenY)
{
	_this->y=givenY;
	// ���⸦ ä��ÿ�
}

Distance Point_distanceTo (Point * _this, Point * givenPoint)
{
	if (_this == NULL || givenPoint == NULL) 
	{
		return InfiniteDistance ; // ���Ѵ� �Ÿ�
	} 
	else 
	{ // �� �� ������ Eucledian Distance�� ���
		Distance xDistance = (_this->x - givenPoint->x) ;
		Distance yDistance = (_this->y - givenPoint->y) ;

		return sqrt(xDistance * xDistance + yDistance * yDistance) ;
	}
}