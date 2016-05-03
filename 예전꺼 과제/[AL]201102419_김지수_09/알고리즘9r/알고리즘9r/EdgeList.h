#pragma once
#include "Global.h"
#include "VertexAndEdge.h"

typedef struct _EdgeList EdgeList;
typedef struct _EdgeNode EdgeNode ;

struct _EdgeList {
int length ; // list�� ����ִ� ����� ����
EdgeNode * head ;
} ;


struct _EdgeNode {
Edge e ;
EdgeNode * next ;
} ;
//Role
//Edge Node�� �����Ǵ� ����Ʈ�̴�.
//Coloring_checkColors()����, edge�� �糡 vertex�� color�� ���� edge���� ��� ���µ� ����Ѵ�.
//Public functions
EdgeList * EdgeList_new () ;
void EdgeList_free (EdgeList * _this) ;
Bool EdgeList_isEmpty (EdgeList * _this) ;
Bool EdgeList_isFull (EdgeList * _this) ;
void EdgeList_add (EdgeList * _this, Edge e) ;