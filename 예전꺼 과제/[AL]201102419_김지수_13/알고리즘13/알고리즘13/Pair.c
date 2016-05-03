#include "Pair.h"

Pair * Pair_new (Point * p1, Point * p2)
{
	Pair * _this = NewObject(Pair) ;
	_this->point1 = p1 ;
	_this->point2 = p2 ;
	
	return _this ;
}

void Pair_free (Pair * _this)
{
	free(_this) ;
}

Distance Pair_distance (Pair * _this)
{
// Pair 객체가 존재하지 않거나 Pair 객체 안에 point 객체가 존재하지 않으면 무한대(InfiniteDistance)를 return 한다
	if (_this == NULL) 
	{ // 객체가 존재하지 않으면 (즉 NULL 객체로 메시지가 전달된 경우)
		return InfiniteDistance ;
	} 
	else 
	{
		// 정상적인 경우에, distance를 계산하여 return 한다
		return Point_distanceTo(_this->point1 , _this->point2) ; // Euclidean Distance
	}
}

Point * Pair_1stPoint (Pair * _this) // pair의 첫번째 점을 얻는다.
{
	return _this->point1 ;
}

void Pair_set1stPoint (Pair * _this, Point * p)
{
	_this->point1 = p ;
}

Point * Pair_2ndPoint (Pair * _this) // pair의 두번째 점을 얻는다.
{
	return _this->point2;
	// 여기를 채우시오
}

void Pair_set2ndPoint (Pair * _this, Point * p)
{
	_this->point2 = p;
	// 여기를 채우시오
}

void Pair_show(Pair * _this, int indentCount, char * title)
{
	Point * p1 = _this->point1 ;
	Point * p2 = _this->point2 ;
	//printfIndentBlanks(indentCount) ;
	//printf("%s:", title) ;
	//printf(" (%f,%f)", Point_xCoordinate(p1),Point_yCoordinate(p1));
	//printf(" (%f,%f)\n", Point_xCoordinate(p2),Point_yCoordinate(p2));
	//printf(" Distance=%f\n", Point_distanceTo(p1, p2)) ;
}