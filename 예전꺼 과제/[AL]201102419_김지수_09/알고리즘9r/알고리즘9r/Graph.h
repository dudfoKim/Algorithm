#pragma once
#include "Global.h"
#include "VertexAndEdge.h"

typedef struct _Graph Graph;

struct _Graph {
int numOfVertices ;
int numOfEdges ;
int ** adjacency ;
} ; // Adjacency matrix�� ������ ���


Graph * Graph_new (int numOfVertices) ;//�־��� vertex �� ��ŭ�� ���� Graph �ʱ� ��ü�� ����
//edge�� ���߿� �߰�
void Graph_free (Graph * _this) ;//�׷��� ��ü�� �Ҹ��Ų��.
Bool Graph_isVertexValid (Graph * _this, Vertex v) ;//�־��� vertex v�� valid���� �Ǵ�
//0���� ũ�ų� ����, _this->numOfVertices���� ������ TRUE, �ƴϸ� FALSE�� ��´�.
Bool Graph_isEdgeValid (Graph * _this, Edge e) ;//�־��� edge e�� valid���� �Ǵ�
//Edge�� ������ vertex�� valid�ϰ�, self-loop�� �ƴϾ�� �Ѵ�
Bool Graph_doesEdgeAlreadyExist (Graph * _this, Edge e) ;//�׷����� Edge e�� �����ϴ����� �˻��Ѵ�.
//�� �Լ��� Coloring_inputNewEdge()���� ���ȴ�.
Bool Graph_insertEdge (Graph * _this, Edge e) ;//�־��� Edge e�� �׷����� �����Ѵ�.
//���������� ���ԵǾ����� TRUE, �ƴϸ� FALSE �� ��´�.
int Graph_numOfVertices(Graph * _this);