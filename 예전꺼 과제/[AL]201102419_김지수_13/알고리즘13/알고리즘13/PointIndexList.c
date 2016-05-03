#include "PointIndexList.h"

PointIndexList * PointIndexList_new (PointSet * points, int givenMaxSize)
{

	// 기본 생성자  최대 크기가 주어진다.
	PointIndexList * _this = NewObject(PointIndexList) ;
	_this->maxSize = givenMaxSize ;
	_this->size = 0 ;
	_this->points = points ;
	_this->body = NewVector(PointIndex, _this->maxSize) ;

	return _this ;
}

/*PointIndexList * PointIndexList_new2 (int givenMaxSize, PointSet * points)
{

	// 기본 생성자  최대 크기가 주어진다.
	PointIndexList * _this = NewObject(PointIndexList) ;
	_this->maxSize = givenMaxSize ;
	_this->size = givenMaxSize ;
	_this->points = points ;
	_this->body = NewVector(PointIndex, _this->maxSize) ;

	return _this ;
}*/

void PointIndexList_free (PointIndexList * _this)
{
	free(_this->body) ;
	free(_this) ;
}

PointIndexList * PointIndexList_newBySortingX (PointSet * points)
{
	// points의 point들이 X 좌표로 정렬된 인덱스 리스트를 생성
	PointIndexList * _this = PointIndexList_new(points,PointSet_size(points)) ;
	int i ;
	
	for (i = 0 ; i < _this->maxSize ; i++)
	{
		_this->body[i] = i ;
	}
	
	_this->size = _this->maxSize ;
	
	PointIndexList_qsortByX(_this) ;
	
	return _this ;
}

PointIndexList * PointIndexList_newBySortingY (PointSet * points)
{
	// points의 point들이 Y 좌표로 정렬된 인덱스 리스트를 생성
	PointIndexList * _this = PointIndexList_new(points, PointSet_size(points) ) ;
	int i ;

	for (i = 0 ; i < _this->maxSize ; i++) 
	{
		_this->body[i] = i ;
	}

	_this->size = _this->maxSize ;

	PointIndexList_qsortByY(_this) ;

	return _this ;
}

void PointIndexList_qsortByX (PointIndexList * _this)
{
	PointIndex indexOfMaxX ;
	PointIndex lastIndex ;
	Point * pointOfMaxX = NULL ;
	Point * pointAtI = NULL ;
	PointIndex i; 
	if (_this->size >= 2)
	{
		// Step 1: 먼저, 정렬 대상인 점 중에서 x 좌표가 가장 큰 점을 찾아 맨 뒤에 갖다 놓는다.
		indexOfMaxX = 0 ;
		pointOfMaxX = PointSet_pointAtIndex(_this->points,indexOfMaxX) ;
	
		for ( i = 1; i < _this->size; i++) 
		{
			pointAtI = PointSet_pointAtIndex(_this->points,i) ;
			/* 두 점을 비교할 때, x 좌표 값이 동일할 경우에는 입력 순서가 나중인 점을 큰 것으로 간주한다.
			if ((Point_xCoordinate(pointOfMaxX) < Point_xCoordinate(pointAtI)) ||
			((Point_xCoordinate(pointOfMaxX) == Point_xCoordinate(pointAtI)) && (indexOfMaxX < i)))
			*/
			// 다음의 if의 조건의 의미는 위의 주석 처리된 if의 조건과 동일한 의미
			// 비교에 등호(<=)가 들어 있음에 유의할 것
		
			if (Point_xCoordinate(pointOfMaxX) <= Point_xCoordinate(pointAtI)) 
			{
				indexOfMaxX = i ;
				pointOfMaxX = pointAtI ;
			}
		}
		
		// 이 시점에서, (_this->index[i]==i)는 TRUE
		lastIndex = _this->body[_this->size-1] ;
		_this->body[_this->size-1] = _this->body[indexOfMaxX] ; ;
		_this->body[indexOfMaxX] = lastIndex ;
		/* 이렇게 해도 동일한 결과를 얻음
		_this->body[_this->size-1] = indexOfMaxX ;
		_this->body[indexOfMaxX] = _this->size-1 ;
		*/
		// Step 2: 실제 정렬은 맨 마지막 점을 제외하고 실행한다.
	
		PointIndexList_qsortByXRecursively(_this, 0, _this->size-2) ;
	}
}

void PointIndexList_qsortByXRecursively (PointIndexList * _this, int left, int right)
{
	int mid ;
	
	if (left < right) 
	{
		mid = PointIndexList_partitionByX(_this, left, right) ;
		PointIndexList_qsortByXRecursively(_this, left, mid-1) ;
		PointIndexList_qsortByXRecursively(_this, mid+1, right) ;
	}
}

int PointIndexList_partitionByX(PointIndexList * _this, int left, int right)
{
	int pivotLoc = left ;
	PointIndex pivotPointIndex = _this->body[pivotLoc] ;
	Point * pivotPoint = PointSet_pointAtIndex(_this->points, pivotPointIndex) ;
	Coordinate pivotX = Point_xCoordinate(pivotPoint) ;
	Coordinate currentXCoordinate ;
	int up = left ;
	int down = right + 1 ;
	//point body로 수정
	do{
		do{
			up++ ;
			currentXCoordinate = Point_xCoordinate(PointSet_pointAtIndex(_this->points, _this->body[up])) ;
		}while ((currentXCoordinate < pivotX) || ((currentXCoordinate == pivotX) && (_this->body[up] < pivotPointIndex)) );

		do{
			down-- ;
			currentXCoordinate = Point_xCoordinate(PointSet_pointAtIndex(_this->points, _this->body[down])) ;
		}while ((currentXCoordinate > pivotX) || ((currentXCoordinate == pivotX) && (_this->body[down] > pivotPointIndex))) ;

		if (up < down) 
		{
			PointIndexList_swap(_this, up, down) ;
		}
	}while (up < down) ;

	PointIndexList_swap(_this, down, pivotLoc) ;

	return down ;
}

void PointIndexList_swap (PointIndexList * _this, int i, int j)
{
	int tempIndex = _this->body[i] ;
	
	_this->body[i] = _this->body[j] ;
	_this->body[j] = tempIndex ;
}

int PointIndexList_compareX (PointIndexList * _this, int i, int j)
{

	Coordinate i_xCoordinate = Point_xCoordinate(PointSet_pointAtIndex(_this->points, _this->body[i])) ;
	Coordinate j_xCoordinate = Point_xCoordinate(PointSet_pointAtIndex(_this->points, _this->body[j])) ;

	if ((i_xCoordinate < j_xCoordinate) || ((i_xCoordinate == j_xCoordinate) && (_this->body[i] < _this->body[j])))
	// x 좌표가 동일하면 PointSet 에서의
	// 원래 순서 (여기서는 입력 순서가 될 것임)를 비교한다
	{
		return -1 ;
	} 
	else 
	{
		return +1 ;
	}
}

void PointIndexList_qsortByY (PointIndexList * _this)
{
// 여기를 채우시오
	PointIndex indexOfMaxY ;
	PointIndex lastIndex ;
	Point * pointOfMaxY = NULL ;
	Point * pointAtI = NULL ;
	PointIndex i;
	
	if (_this->size >= 2)
	{
		// Step 1: 먼저, 정렬 대상인 점 중에서 x 좌표가 가장 큰 점을 찾아 맨 뒤에 갖다 놓는다.
		indexOfMaxY = 0 ;
		pointOfMaxY = PointSet_pointAtIndex(_this->points,indexOfMaxY) ;
	
		for (i = 1; i < _this->size; i++) 
		{
			pointAtI = PointSet_pointAtIndex(_this->points,i) ;
			/* 두 점을 비교할 때, x 좌표 값이 동일할 경우에는 입력 순서가 나중인 점을 큰 것으로 간주한다.
			if ((Point_xCoordinate(pointOfMaxX) < Point_xCoordinate(pointAtI)) ||
			((Point_xCoordinate(pointOfMaxX) == Point_xCoordinate(pointAtI)) && (indexOfMaxX < i)))
			*/
			// 다음의 if의 조건의 의미는 위의 주석 처리된 if의 조건과 동일한 의미
			// 비교에 등호(<=)가 들어 있음에 유의할 것
	
			if (Point_yCoordinate(pointOfMaxY) <= Point_yCoordinate(pointAtI)) 
			{
				indexOfMaxY = i ;
				pointOfMaxY = pointAtI ;
			}
		}
		
		// 이 시점에서, (_this->index[i]==i)는 TRUE
		lastIndex = _this->body[_this->size-1] ;
		_this->body[_this->size-1] = _this->body[indexOfMaxY] ; ;
		_this->body[indexOfMaxY] = lastIndex ;
		/* 이렇게 해도 동일한 결과를 얻음
		_this->body[_this->size-1] = indexOfMaxX ;
		_this->body[indexOfMaxX] = _this->size-1 ;
		*/
		// Step 2: 실제 정렬은 맨 마지막 점을 제외하고 실행한다.
		PointIndexList_qsortByYRecursively(_this, 0, _this->size-2) ;
	}
}

void PointIndexList_qsortByYRecursively (PointIndexList * _this, int left, int right)
{
// 여기를 채우시오
	int mid ;
	
	if (left < right) 
	{
		mid = PointIndexList_partitionByY(_this, left, right) ;
		PointIndexList_qsortByYRecursively(_this, left, mid-1) ;
		PointIndexList_qsortByYRecursively(_this, mid+1, right) ;
	}
}

int PointIndexList_partitionByY (PointIndexList * _this, int left, int right)
{
// 여기를 채우시오
	int pivotLoc = left ;
	PointIndex pivotPointIndex = _this->body[pivotLoc] ;
	Point * pivotPoint = PointSet_pointAtIndex(_this->points, pivotPointIndex) ;
	Coordinate pivotY = Point_yCoordinate(pivotPoint) ;
	Coordinate currentYCoordinate ;
	int up = left ;
	int down = right + 1 ;
	//point body로 수정
	do{
		do{
			up++ ;
			currentYCoordinate = Point_yCoordinate(PointSet_pointAtIndex(_this->points, _this->body[up])) ;
		}while ((currentYCoordinate < pivotY) || ((currentYCoordinate == pivotY) && (_this->body[up] < pivotPointIndex)) );

		do{
			down-- ;
			currentYCoordinate = Point_yCoordinate(PointSet_pointAtIndex(_this->points, _this->body[down])) ;
		}while ((currentYCoordinate > pivotY) || ((currentYCoordinate == pivotY) && (_this->body[down] > pivotPointIndex))) ;

		if (up < down) 
		{
			PointIndexList_swap(_this, up, down) ;
		}
	}while (up < down) ;

	PointIndexList_swap(_this, down, pivotLoc) ;

	return down ;
}

int PointIndexList_compareY (PointIndexList * _this, int i, int j)
{
// 여기를 채우시오
	Coordinate i_yCoordinate = Point_yCoordinate(PointSet_pointAtIndex(_this->points, _this->body[i])) ;
	Coordinate j_yCoordinate = Point_yCoordinate(PointSet_pointAtIndex(_this->points, _this->body[j])) ;

	if ((i_yCoordinate < j_yCoordinate) || ((i_yCoordinate == j_yCoordinate) && (_this->body[i] < _this->body[j])))
	// x 좌표가 동일하면 PointSet 에서의
	// 원래 순서 (여기서는 입력 순서가 될 것임)를 비교한다
	{
		return -1 ;
	} 
	else 
	{
		return +1 ;
	}
}

int PointIndexList_size (PointIndexList * _this) 
{
	return _this->size;
}

PointIndex PointIndexList_pointIndex (PointIndexList * _this, int indexListLoc) 
{
	return _this->body[indexListLoc];
}
Bool PointIndexList_add (PointIndexList * _this, PointIndex anIndex) 
{
	_this->body[_this->size]=anIndex;
	_this->size++;

	return T;
}