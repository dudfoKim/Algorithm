#pragma once
#include "Global.h"
#include "VertexAndEdge.h"

typedef struct _VertexQueue VertexQueue;
typedef struct _VertexNode VertexNode;

struct _VertexQueue {
int length ; // list�� ����ִ� ����� ����
VertexNode * front ;
VertexNode * rear ;
} ;


struct _VertexNode {
Vertex v ;
VertexNode * next ;
} ;

//Role
//�־��� �׷����� ����, BFS�� �����ϱ� ���� �ʿ���, vertex�� ť
//Public functions
VertexQueue * VertexQueue_new ();
void VertexQueue_free (VertexQueue * _this);
void VertexQ_add (VertexQueue * _this, Vertex v);
Vertex VertexQueue_delete (VertexQueue * _this);
Bool VertexQueue_isEmpty (VertexQueue * _this);