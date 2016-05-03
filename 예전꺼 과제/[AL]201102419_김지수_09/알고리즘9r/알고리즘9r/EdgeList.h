#pragma once
#include "Global.h"
#include "VertexAndEdge.h"

typedef struct _EdgeList EdgeList;
typedef struct _EdgeNode EdgeNode ;

struct _EdgeList {
int length ; // list에 들어있는 노드의 개수
EdgeNode * head ;
} ;


struct _EdgeNode {
Edge e ;
EdgeNode * next ;
} ;
//Role
//Edge Node로 구성되는 리스트이다.
//Coloring_checkColors()에서, edge의 양끝 vertex의 color가 같은 edge들을 모아 놓는데 사용한다.
//Public functions
EdgeList * EdgeList_new () ;
void EdgeList_free (EdgeList * _this) ;
Bool EdgeList_isEmpty (EdgeList * _this) ;
Bool EdgeList_isFull (EdgeList * _this) ;
void EdgeList_add (EdgeList * _this, Edge e) ;