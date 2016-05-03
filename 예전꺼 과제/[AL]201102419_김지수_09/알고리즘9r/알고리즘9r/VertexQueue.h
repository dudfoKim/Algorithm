#pragma once
#include "Global.h"
#include "VertexAndEdge.h"

typedef struct _VertexQueue VertexQueue;
typedef struct _VertexNode VertexNode;

struct _VertexQueue {
int length ; // list에 들어있는 노드의 개수
VertexNode * front ;
VertexNode * rear ;
} ;


struct _VertexNode {
Vertex v ;
VertexNode * next ;
} ;

//Role
//주어진 그래프에 대해, BFS를 수행하기 위해 필요한, vertex의 큐
//Public functions
VertexQueue * VertexQueue_new ();
void VertexQueue_free (VertexQueue * _this);
void VertexQ_add (VertexQueue * _this, Vertex v);
Vertex VertexQueue_delete (VertexQueue * _this);
Bool VertexQueue_isEmpty (VertexQueue * _this);