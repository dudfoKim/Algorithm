#include "PointSet.h"

PointSet * PointSet_new (int givenMaxSize)
{
	PointSet * _this = NewObject(PointSet) ;
	_this->maxSize = givenMaxSize ;
	_this->body = NewVector(Point*, givenMaxSize) ;
	_this->size = 0 ;
	
	return _this ;
}
void PointSet_free (PointSet * _this)
{
	free(_this->body);
	free(_this);
	// 여기를 채우시오

}
Bool PointSet_isEmpty (PointSet * _this)
{
	if(_this->size==0)
	{
		return T;
	}

	return F;

	// 여기를 채우시오

}
Bool PointSet_isFull (PointSet * _this)
{
	if(_this->size==_this->maxSize)
	{
		return T;
	}
	
	return F;
	// 여기를 채우시오

}

Bool PointSet_addPoint (PointSet * _this, Point * p)
{
	if (_this->size < _this->maxSize) 
	{
		_this->body[_this->size] = p ;
		_this->size++ ;
	
		return T ;
	} 
	else 
	{
		return F ; // set is full, so no more space
	}
}
int PointSet_size (PointSet * _this)
{
	return _this->size;
	// 여기를 채우시오
}
Bool PointSet_isPointIndexOK (PointSet * _this, PointIndex index)
{
	if(index < _this->size)
	{
		return T ;
	}
	
	return F;
}
Point * PointSet_pointAtIndex (PointSet * _this, PointIndex index)
{
	if (index < _this->size) 
	{
		return _this->body[index] ;
	} 
	else 
	{
		return NULL ;
	}
}