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
//�־��� Edge ����Ʈ�� ���ҵ��� edge���� ���ʷ� �ϳ��� ��´�
//Coloring_showAllEdges()���� ���
//Public functions
EdgeListIterator * EdgeListIterator_new (EdgeList * edgeList) ;
void EdgeListIterator_free (EdgeListIterator * _this) ;
void EdgeListIterator_begin (EdgeListIterator * _this) ;
Bool EdgeListIterator_end (EdgeListIterator * _this) ;
Edge EdgeListIterator_currentElement (EdgeListIterator * _this) ;
void EdgeListIterator_next (EdgeListIterator * _this) ;