#pragma once
#include "Global.h"
#include "VertexAndEdge.h"
#include "EdgeList.h"

typedef struct _EdgeListIterator EdgeListIterator;

struct _EdgeListIterator
{
	EdgeList * edgelist;
	EdgeNode * curNode;
};
//Role
//주어진 Edge 리스트의 원소들인 edge들을 차례로 하나씩 얻는다
//Coloring_showAllEdges()에서 사용
//Public functions
EdgeListIterator * EdgeListIterator_new (EdgeList * edgeList) ;
void EdgeListIterator_free (EdgeListIterator * _this) ;
void EdgeListIterator_begin (EdgeListIterator * _this) ;
Bool EdgeListIterator_end (EdgeListIterator * _this) ;
Edge EdgeListIterator_currentElement (EdgeListIterator * _this) ;
void EdgeListIterator_next (EdgeListIterator * _this) ;