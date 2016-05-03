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
// Pair ��ü�� �������� �ʰų� Pair ��ü �ȿ� point ��ü�� �������� ������ ���Ѵ�(InfiniteDistance)�� return �Ѵ�
	if (_this == NULL) 
	{ // ��ü�� �������� ������ (�� NULL ��ü�� �޽����� ���޵� ���)
		return InfiniteDistance ;
	} 
	else 
	{
		// �������� ��쿡, distance�� ����Ͽ� return �Ѵ�
		return Point_distanceTo(_this->point1 , _this->point2) ; // Euclidean Distance
	}
}

Point * Pair_1stPoint (Pair * _this) // pair�� ù��° ���� ��´�.
{
	return _this->point1 ;
}

void Pair_set1stPoint (Pair * _this, Point * p)
{
	_this->point1 = p ;
}

Point * Pair_2ndPoint (Pair * _this) // pair�� �ι�° ���� ��´�.
{
	return _this->point2;
	// ���⸦ ä��ÿ�
}

void Pair_set2ndPoint (Pair * _this, Point * p)
{
	_this->point2 = p;
	// ���⸦ ä��ÿ�
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