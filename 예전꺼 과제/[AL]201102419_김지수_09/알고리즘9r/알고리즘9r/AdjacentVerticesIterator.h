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
//�־��� �׷����� ������ vertex (from_Vertex)�� ����, �� vertex�� �پ��ִ� edge��, �� �� from_vertex�� �̿��� to_vertex���� ���ʷ� �˻��Ѵ�.
//Public functions
AdjacentVerticesIterator * AdjacentVerticesIterator_new (Graph * graph) ;
void AdjacentVerticesIterator_free (AdjacentVerticesIterator * _this) ;
void AdjacentVerticesIterator_begin (AdjacentVerticesIterator * _this, Vertex v) ;
Bool AdjacentVerticesIterator_end(AdjacentVerticesIterator * _this) ;
Vertex AdjacentVerticesIterator_currentElement(AdjacentVerticesIterator * _this) ;
void AdjacentVerticesIterator_next (AdjacentVerticesIterator * _this) ;