#include "PointIndexList.h"

PointIndexList * PointIndexList_new (PointSet * points, int givenMaxSize)
{

	// �⺻ ������  �ִ� ũ�Ⱑ �־�����.
	PointIndexList * _this = NewObject(PointIndexList) ;
	_this->maxSize = givenMaxSize ;
	_this->size = 0 ;
	_this->points = points ;
	_this->body = NewVector(PointIndex, _this->maxSize) ;

	return _this ;
}

/*PointIndexList * PointIndexList_new2 (int givenMaxSize, PointSet * points)
{

	// �⺻ ������  �ִ� ũ�Ⱑ �־�����.
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
	// points�� point���� X ��ǥ�� ���ĵ� �ε��� ����Ʈ�� ����
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
	// points�� point���� Y ��ǥ�� ���ĵ� �ε��� ����Ʈ�� ����
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
		// Step 1: ����, ���� ����� �� �߿��� x ��ǥ�� ���� ū ���� ã�� �� �ڿ� ���� ���´�.
		indexOfMaxX = 0 ;
		pointOfMaxX = PointSet_pointAtIndex(_this->points,indexOfMaxX) ;
	
		for ( i = 1; i < _this->size; i++) 
		{
			pointAtI = PointSet_pointAtIndex(_this->points,i) ;
			/* �� ���� ���� ��, x ��ǥ ���� ������ ��쿡�� �Է� ������ ������ ���� ū ������ �����Ѵ�.
			if ((Point_xCoordinate(pointOfMaxX) < Point_xCoordinate(pointAtI)) ||
			((Point_xCoordinate(pointOfMaxX) == Point_xCoordinate(pointAtI)) && (indexOfMaxX < i)))
			*/
			// ������ if�� ������ �ǹ̴� ���� �ּ� ó���� if�� ���ǰ� ������ �ǹ�
			// �񱳿� ��ȣ(<=)�� ��� ������ ������ ��
		
			if (Point_xCoordinate(pointOfMaxX) <= Point_xCoordinate(pointAtI)) 
			{
				indexOfMaxX = i ;
				pointOfMaxX = pointAtI ;
			}
		}
		
		// �� ��������, (_this->index[i]==i)�� TRUE
		lastIndex = _this->body[_this->size-1] ;
		_this->body[_this->size-1] = _this->body[indexOfMaxX] ; ;
		_this->body[indexOfMaxX] = lastIndex ;
		/* �̷��� �ص� ������ ����� ����
		_this->body[_this->size-1] = indexOfMaxX ;
		_this->body[indexOfMaxX] = _this->size-1 ;
		*/
		// Step 2: ���� ������ �� ������ ���� �����ϰ� �����Ѵ�.
	
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
	//point body�� ����
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
	// x ��ǥ�� �����ϸ� PointSet ������
	// ���� ���� (���⼭�� �Է� ������ �� ����)�� ���Ѵ�
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
// ���⸦ ä��ÿ�
	PointIndex indexOfMaxY ;
	PointIndex lastIndex ;
	Point * pointOfMaxY = NULL ;
	Point * pointAtI = NULL ;
	PointIndex i;
	
	if (_this->size >= 2)
	{
		// Step 1: ����, ���� ����� �� �߿��� x ��ǥ�� ���� ū ���� ã�� �� �ڿ� ���� ���´�.
		indexOfMaxY = 0 ;
		pointOfMaxY = PointSet_pointAtIndex(_this->points,indexOfMaxY) ;
	
		for (i = 1; i < _this->size; i++) 
		{
			pointAtI = PointSet_pointAtIndex(_this->points,i) ;
			/* �� ���� ���� ��, x ��ǥ ���� ������ ��쿡�� �Է� ������ ������ ���� ū ������ �����Ѵ�.
			if ((Point_xCoordinate(pointOfMaxX) < Point_xCoordinate(pointAtI)) ||
			((Point_xCoordinate(pointOfMaxX) == Point_xCoordinate(pointAtI)) && (indexOfMaxX < i)))
			*/
			// ������ if�� ������ �ǹ̴� ���� �ּ� ó���� if�� ���ǰ� ������ �ǹ�
			// �񱳿� ��ȣ(<=)�� ��� ������ ������ ��
	
			if (Point_yCoordinate(pointOfMaxY) <= Point_yCoordinate(pointAtI)) 
			{
				indexOfMaxY = i ;
				pointOfMaxY = pointAtI ;
			}
		}
		
		// �� ��������, (_this->index[i]==i)�� TRUE
		lastIndex = _this->body[_this->size-1] ;
		_this->body[_this->size-1] = _this->body[indexOfMaxY] ; ;
		_this->body[indexOfMaxY] = lastIndex ;
		/* �̷��� �ص� ������ ����� ����
		_this->body[_this->size-1] = indexOfMaxX ;
		_this->body[indexOfMaxX] = _this->size-1 ;
		*/
		// Step 2: ���� ������ �� ������ ���� �����ϰ� �����Ѵ�.
		PointIndexList_qsortByYRecursively(_this, 0, _this->size-2) ;
	}
}

void PointIndexList_qsortByYRecursively (PointIndexList * _this, int left, int right)
{
// ���⸦ ä��ÿ�
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
// ���⸦ ä��ÿ�
	int pivotLoc = left ;
	PointIndex pivotPointIndex = _this->body[pivotLoc] ;
	Point * pivotPoint = PointSet_pointAtIndex(_this->points, pivotPointIndex) ;
	Coordinate pivotY = Point_yCoordinate(pivotPoint) ;
	Coordinate currentYCoordinate ;
	int up = left ;
	int down = right + 1 ;
	//point body�� ����
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
// ���⸦ ä��ÿ�
	Coordinate i_yCoordinate = Point_yCoordinate(PointSet_pointAtIndex(_this->points, _this->body[i])) ;
	Coordinate j_yCoordinate = Point_yCoordinate(PointSet_pointAtIndex(_this->points, _this->body[j])) ;

	if ((i_yCoordinate < j_yCoordinate) || ((i_yCoordinate == j_yCoordinate) && (_this->body[i] < _this->body[j])))
	// x ��ǥ�� �����ϸ� PointSet ������
	// ���� ���� (���⼭�� �Է� ������ �� ����)�� ���Ѵ�
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