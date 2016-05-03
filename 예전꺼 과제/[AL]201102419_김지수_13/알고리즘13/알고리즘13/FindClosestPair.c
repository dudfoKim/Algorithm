#include "FindClosestPair.h"

Pair * FindClosestPair_runRecursively(FindClosestPair * _this, PointIndexList * Px, PointIndexList * Py) ;

Pair * FindClosestPair_closestPairDirectlyFromSmallPointSet(FindClosestPair * _this, PointIndexList * Px) ;

Pair * FindClosestPair_closestPairFromDeltaBand (FindClosestPair * _this, PointIndexList * Py, SeparationLine line, Distance delta) ;

PointIndexList * FindClosestPair_deltaBand(FindClosestPair * _this, PointIndexList * Py, SeparationLine line, Distance delta) ;

Pair * FindClosestPair_closestPairFromHereTo6Neighbors (FindClosestPair * _this, PointIndexList * Sy, int here) ;

SeparationLine FindClosestPair_separationLine (FindClosestPair * _this, PointIndexList * Px) ;

PointIndexListPair FindClosestPair_separatePoints(FindClosestPair * _this, PointIndexList * iList, SeparationLine line) ;

void FindClosestPair_showSeparationLine(FindClosestPair * _this, SeparationLine line) ;



FindClosestPair * FindClosestPair_new (PointSet * givenPoints)
{
	FindClosestPair * _this = NewObject(FindClosestPair) ;
	_this->points = givenPoints ;
	_this->recursionDepth = 0 ; // only for debugging
	
	return _this ;
}

void FindClosestPair_free(FindClosestPair * _this)
{
	// _this->points�� �ܺ� (App ��ü)�κ��� read only �������� �޾����Ƿ�
	// �� �Ҹ��� App ��ü�� å������.
	free (_this) ;
}

Pair * FindClosestPair_run (FindClosestPair * _this)
{
	Pair * closestPair ;
	PointIndexList * Px = PointIndexList_newBySortingX (_this->points) ; // copy & sort by X
	
	PointIndexList * Py = PointIndexList_newBySortingY (_this->points) ; // copy & sort by Y
	
	//PointIndexList_showPoints(Px, _this->recursionDepth, "<Initial Point Index List Px>") ;
	//PointIndexList_showPoints(Py, _this->recursionDepth, "<Initial Point Index List Py>") ;
	closestPair = FindClosestPair_runRecursively (_this, Px, Py) ;
	PointIndexList_free(Px) ;
	PointIndexList_free(Py) ;
	
	return closestPair ;
}

Pair * FindClosestPair_runRecursively (FindClosestPair * _this, PointIndexList * Px, PointIndexList * Py)
{
	Pair * closestPair;
	Pair * closestPairForLeft;
	Pair * closestPairForRight;
	SeparationLine line;
	float delta;
	Pair * closestPairFromDeltaBand;
	PointIndexListPair pairSeparatedFromPx;
	PointIndexListPair pairSeparatedFromPy ;
	// only for debugging
	_this->recursionDepth++ ;
//	printfIndentBlanks(_this->recursionDepth-1) ;
	//printf(">>> Begin of Recursion Depth: %d\n", _this->recursionDepth) ;
	
	if (PointIndexList_size(Px) <= 3) 
	{ // O(1)
	
		closestPair = FindClosestPair_closestPairDirectlyFromSmallPointSet(_this,Px) ;
		

	// only for debugging
		//Pair_show(closestPair,_this->recursionDepth, "Closest Pair from Small Point Set") ;
		//printfIndentBlanks(_this->recursionDepth-1) ;
		//printf(">>> End of Recursion Depth: %d\n",_this->recursionDepth) ;
		_this->recursionDepth-- ;
		
		return closestPair ;
	}
	
	line = FindClosestPair_separationLine(_this,Px) ; // Separation Line

	FindClosestPair_showSeparationLine (_this, line) ;
	
	// Construct Qx, Qy, Rx, Ry from Px and Py; // O(n)
	
	pairSeparatedFromPx = FindClosestPair_separatePoints (_this, Px, line) ;
	
	//PointIndexList_showPoints(pairSeparatedFromPx.left, _this->recursionDepth,"<Left Index List separated from Px>") ;
	
	//PointIndexList_showPoints(pairSeparatedFromPx.right,_this->recursionDepth,"<Right Index List separated from Px>") ;
	
	pairSeparatedFromPy = FindClosestPair_separatePoints (_this, Py, line) ;
	
	//PointIndexList_showPoints(pairSeparatedFromPy.left,_this->recursionDepth,"<Left Index List separated from Py>") ;
	
	//PointIndexList_showPoints(pairSeparatedFromPy.right,_this->recursionDepth,"<Right Index List separated from Py>") ;
	
	closestPairForLeft = FindClosestPair_runRecursively(_this, pairSeparatedFromPx.left, pairSeparatedFromPy.left) ; // T(n/2)
	
	//Pair_show(closestPairForLeft,_this->recursionDepth,"Closest Pair For Left ") ;
	
	closestPairForRight = FindClosestPair_runRecursively(_this, pairSeparatedFromPx.right, pairSeparatedFromPy.right) ;//T(n/2)
	
	//Pair_show(closestPairForRight,_this->recursionDepth,"Closest Pair For Right") ;
	
	if ( Pair_distance(closestPairForLeft) < Pair_distance(closestPairForRight) ) 
	{ // O(1)
		closestPair = closestPairForLeft ;
		Pair_free(closestPairForRight) ;
	}
	
	else 
	{
		closestPair = closestPairForRight ;
		Pair_free(closestPairForLeft) ;
	}
	
	//Pair_show(closestPair, _this->recursionDepth, "Closest Pair For Left & Right") ;

	delta = Pair_distance(closestPair) ;

	closestPairFromDeltaBand = FindClosestPair_closestPairFromDeltaBand(_this, Py, line, delta) ;

	if (closestPairFromDeltaBand != NULL) 
	{
		//Pair_show(closestPairFromDeltaBand, _this->recursionDepth, "Closest Pair From Delta Band") ;

		if (Pair_distance(closestPairFromDeltaBand) < Pair_distance(closestPair)) 
		{
			Pair_free(closestPair) ;
			closestPair = closestPairFromDeltaBand ;
		} 
		else 
		{
			Pair_free(closestPairFromDeltaBand) ;
		}
	}

	PointIndexList_free(pairSeparatedFromPx.left) ;
	PointIndexList_free(pairSeparatedFromPx.right) ;
	PointIndexList_free(pairSeparatedFromPy.left) ;
	PointIndexList_free(pairSeparatedFromPy.right) ;
	//Pair_show(closestPair, _this->recursionDepth, "ClosestPair From Recursion") ;
//	printfIndentBlanks(_this->recursionDepth-1) ;
	//printf(">>> End of Recursion Depth: %d\n", _this->recursionDepth) ;
	
	return closestPair ;
} // End of runRecursively()

Pair * FindClosestPair_closestPairDirectlyFromSmallPointSet(FindClosestPair * _this, PointIndexList * Px)
{
	//PointSet �� ���� ������ 3 �� ������ ��쿡 closestPair�� ã�´�
	// PointSet �� ���� ������ 3 �� ������ ��쿡 closestPair�� ã�´�
	Pair * closestPair = NULL ;
	Point * p0; 
	Point * p1; 
	Point * p2;
	Distance minDistance;

	if (PointIndexList_size(Px) > 1) 
	{ // �� ������ 1�� �����̸� ��� �Ҵ�, NULL ��ü�� return
		p0 = PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(Px, 0)) ;
		p1 = PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(Px, 1)) ;
		p2 = NULL ;
		
		closestPair = Pair_new(p0, p1) ;
		minDistance = Point_distanceTo(p0, p1) ;
	
		if (PointIndexList_size(Px) == 3) 
		{
			p2 = PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(Px, 2)) ;
	
			if (Point_distanceTo(p0, p2) < minDistance)
			{
				minDistance = Point_distanceTo(p0, p2) ;
				Pair_set2ndPoint(closestPair, p2) ;
			}
	
			if (Point_distanceTo(p1, p2) < minDistance) 
			{
				minDistance = Point_distanceTo(p1, p2) ;
				Pair_set1stPoint(closestPair, p1) ;
				Pair_set2ndPoint(closestPair, p2) ;
			}
		}
	}
	
	return closestPair ;
}

Pair * FindClosestPair_closestPairFromDeltaBand(FindClosestPair * _this, PointIndexList * Py, SeparationLine line, Distance delta) 
{
	//Py�� Separation line�� delta ���� ���� �����Ǵ� Delta Band �ȿ����� closest Pair�� ã�´�
	//�� �Լ����� FindClosestPair_deltaBand()�� FindClosestPair_closestPairFromHereTo6Neighbors() �� ����Ѵ�
	//Py�� Separation line�� delta ���� ���� �����Ǵ� Delta Band �ȿ����� closest Pair�� ã�´�
	// �� �Լ����� FindClosestPair_deltaBand()�� FindClosestPair_closestPairFromHereToNeighbors() �� ����Ѵ�
	Pair * closestPair = NULL ;
	Pair * closestPairToNeighbors = NULL ;
	PointIndexList * Sy = FindClosestPair_deltaBand(_this, Py, line, delta) ;
	int Sy_size = PointIndexList_size(Sy) ;
	int here = 0;
	
	if (Sy_size > 1) 
	{
		here = 0 ;
		closestPair = FindClosestPair_closestPairFromHereTo6Neighbors(_this, Sy, here) ;
		
		for (here = 1; here < Sy_size-1; here++) 
		{	// O(n)
			// each point s of Sy in y-order
			// For each next #(NumOfNewghbors) neighbor points, // O(NumOfNeighbors) = O(1)
	
			closestPairToNeighbors = FindClosestPair_closestPairFromHereTo6Neighbors(_this, Sy, here) ;
	
			if (Pair_distance(closestPairToNeighbors) < Pair_distance(closestPair)) 
			{
				closestPair = closestPairToNeighbors ;
			} 
			else 
			{
				Pair_free(closestPairToNeighbors) ;
			}
		}
	}
	
	PointIndexList_free(Sy) ;
	
	return closestPair ;
}

PointIndexList * FindClosestPair_deltaBand(FindClosestPair * _this, PointIndexList * Py, SeparationLine line, Distance delta)
{
	//Delta Band �ȿ� ��� �ִ� ������ ����Ʈ�� Py�κ��� line�� delta ���� �̿��Ͽ� ��󳽴�
	Point * p = NULL ;
	PointIndex pointIndex ;
	int i;

	int sizeOfPy = PointIndexList_size(Py) ;

	PointIndexList * Sy = PointIndexList_new (sizeOfPy, _this->points) ;

	for ( i = 0 ; i < sizeOfPy ; i++) 
	{
		pointIndex = PointIndexList_pointIndex(Py, i);
		p = PointSet_pointAtIndex(_this->points, pointIndex) ;

		if (abs(Point_xCoordinate(p)-line.midX) < delta) 
		{
			PointIndexList_add(Sy,pointIndex) ;
		}
	}

	//PointIndexList_showPoints(Sy, _this->recursionDepth, "<Points in Delta Band>");

	return Sy ;
}

Pair * FindClosestPair_closestPairFromHereTo6Neighbors (FindClosestPair * _this, PointIndexList * Sy, int here) 
{
	//�־��� index here �� �������� Sy ����Ʈ���� �� ���ķ� ������ �ִ� 6 ���� ���� �߿��� here �� ���� ����� ���� ã�´�
	Distance distanceToNeighbor ;
	Point * neighborPoint = NULL ;
	Point * currentPoint = PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(Sy, here)) ;
	Pair * closestPair = Pair_new(currentPoint, PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(Sy, here+1))) ;
	Distance minDistance = Pair_distance(closestPair) ;
	int lastNeighbor = ((here+NumOfNeighbors) < PointIndexList_size(Sy)) ? here+NumOfNeighbors : PointIndexList_size(Sy)-1 ;
	int neighbor = 0;

	for (neighbor = here+1 ; neighbor <= lastNeighbor; neighbor++) 
	{
		neighborPoint = PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(Sy, neighbor)) ;
		distanceToNeighbor = Point_distanceTo(currentPoint, neighborPoint) ;
	
		if (distanceToNeighbor < minDistance ) 
		{
			minDistance = distanceToNeighbor ;
			Pair_set2ndPoint(closestPair, neighborPoint) ;
		}
	}
	
	return closestPair ;
}


SeparationLine FindClosestPair_separationLine(FindClosestPair * _this, PointIndexList * Px)
{
	//Px�κ��� �¿�� ������ ���� Seperation Line�� ã�´�
	//�ܼ��� ������ ������ ���� ������
	SeparationLine line ;
	line.midIndex = PointIndexList_pointIndex(Px, (PointIndexList_size(Px) / 2)) ;
	line.midX = Point_xCoordinate(PointSet_pointAtIndex(_this->points,line.midIndex)) ;

	return line ;
}
PointIndexListPair FindClosestPair_separatePoints(FindClosestPair * _this, PointIndexList * iList, SeparationLine line)
{
	//Separation Line�� �������� iList�� ���� index���� ������ ���� �ε������ ������ ���� �ε������ ������.
	Point * p = NULL ;
	PointIndex pointIndex ;
	PointIndexListPair listPair ;
	int sizeOfList = PointIndexList_size(iList) ;
	int i=0; 

	listPair.left = PointIndexList_new(_this->points, sizeOfList) ;
	listPair.right = PointIndexList_new(_this->points, sizeOfList) ;
	
	
	for (i = 0 ; i < sizeOfList ; i++) 
	{
		pointIndex = PointIndexList_pointIndex(iList, i);
		p = PointSet_pointAtIndex(_this->points, PointIndexList_pointIndex(iList, i)) ;
	
		if (Point_xCoordinate(p) < line.midX) 
		{
			PointIndexList_add(listPair.left, pointIndex) ;
		} 
		else if (Point_xCoordinate(p) > line.midX)
		{
			PointIndexList_add(listPair.right, pointIndex) ;
		} 
		else 
		{ // ���� �и���(line) ���� ���� ���
			if (pointIndex < line.midIndex) 
			{
	
				PointIndexList_add(listPair.left, pointIndex) ;
			} 
			else 
			{
				PointIndexList_add(listPair.right, pointIndex) ;
			}
		}
	}
	
	return listPair ;
}
	
void FindClosestPair_showSeparationLine(FindClosestPair * _this, SeparationLine line) 
{
	//Only for debugging
//	printfIndentBlanks(_this->recursionDepth) ;
	//printf("Separation Line: point[%d].x = %f\n",line.midIndex,line.midX) ;
}