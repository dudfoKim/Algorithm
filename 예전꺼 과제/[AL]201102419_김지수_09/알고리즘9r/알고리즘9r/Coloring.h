#pragma once
#include "Global.h"
#include "Graph.h"
#include "EdgeList.h"
#include "VertexAndEdge.h"
#include "AdjacentVerticesIterator.h"
#include "VertexQueue.h"
#include "Graph.h"
#include "EdgeListIterator.h"

typedef struct _Coloring Coloring ;
typedef enum {NONE, RED, BLUE} Color ;

struct _Coloring 
{
	int numOfVertices ;
	int numOfEdges ;
	Graph * graph ;
	Color * color ; // �� vertex�� color�� ������ �迭
	Vertex startingVertex ;
	EdgeList * sameColorEdges ; // �� ���� ���� edge���� ����Ʈ
} ;

Coloring * Coloring_new () ;//Coloring ��ü�� �����Ѵ�.
void Coloring_free (Coloring * _this) ;//��ü�� �Ҹ��Ų��.
//����, _this �� �����ϰ� �ִ� (��, member variable�� �����) ��� ��ü
//����������, _this ��ü ��ü
void Coloring_inputAndMakeGraph (Coloring * _this) ;//�ܺηκ��� vertex�� edge���� �Է� �޾� �׷����� �����.
//Vertex�� �ּ��� 1 �� �̻� �����ؾ� �Ѵ�.
//Edge�� 1�� �Ǵ� �� �̻� �����ؾ� �Ѵ�.
void Coloring_showGraph (Coloring * _this) ;//���� ������ �ִ� �׷����� �����ش�.
void Coloring_runColoring (Coloring * _this) ;//Coloring�� �����Ѵ�.
void Coloring_showColoring (Coloring * _this) ;//Coloring ����� �����ش�.
void Coloring_checkColors (Coloring * _this);