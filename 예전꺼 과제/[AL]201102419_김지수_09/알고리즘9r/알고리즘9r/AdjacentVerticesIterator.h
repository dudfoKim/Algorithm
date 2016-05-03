#pragma once
#include "Global.h"
#include "Graph.h"

typedef struct _AdjacentVerticesIterator AdjacentVerticesIterator;

struct _AdjacentVerticesIterator {
Graph * graph ;
Vertex fromV ;
int curLoc ;
} ;
//Role
//주어진 그래프의 지정된 vertex (from_Vertex)에 대해, 그 vertex에 붙어있는 edge들, 즉 그 from_vertex에 이웃한 to_vertex들을 차례로 검색한다.
//Public functions
AdjacentVerticesIterator * AdjacentVerticesIterator_new (Graph * graph) ;
void AdjacentVerticesIterator_free (AdjacentVerticesIterator * _this) ;
void AdjacentVerticesIterator_begin (AdjacentVerticesIterator * _this, Vertex v) ;
Bool AdjacentVerticesIterator_end(AdjacentVerticesIterator * _this) ;
Vertex AdjacentVerticesIterator_currentElement(AdjacentVerticesIterator * _this) ;
void AdjacentVerticesIterator_next (AdjacentVerticesIterator * _this) ;