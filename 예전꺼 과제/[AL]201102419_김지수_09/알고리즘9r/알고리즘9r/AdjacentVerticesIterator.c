#include "AdjacentVerticesIterator.h"



AdjacentVerticesIterator * AdjacentVerticesIterator_new (Graph * graph)
{
	AdjacentVerticesIterator * _this = NewObject(AdjacentVerticesIterator) ;
	_this->graph = graph ;
	_this->curLoc=0;

	return _this ;

}
void AdjacentVerticesIterator_free (AdjacentVerticesIterator * _this) 
{
	
	free(_this);
}
void AdjacentVerticesIterator_begin (AdjacentVerticesIterator * _this, Vertex v) 
{
	_this->fromV=v;
}
Bool AdjacentVerticesIterator_end(AdjacentVerticesIterator * _this) 
{
	if(_this->graph->numOfVertices==_this->curLoc)
	{
		_this->curLoc=0;
		return T;
	}
	return F;
}
Vertex AdjacentVerticesIterator_currentElement(AdjacentVerticesIterator * _this) 
{
	return (_this->graph->adjacency[_this->fromV][_this->curLoc]);

}

void AdjacentVerticesIterator_next (AdjacentVerticesIterator * _this) 
{
	_this->curLoc++;
}