#pragma once
#include "Global.h"
#include "MCST_MSG.h"

class Graph
{
private:
	int numOfVertices ;
	int numOfEdges ;
	Cost ** adjacency ; // ������ �迭
public:
	Graph::Graph (int numOfVertices, int numOfEdges);
	Graph::~Graph ();
	int Graph::getnumOfVertices();//�׷����� vertex ���� �˷��ش�.
	bool Graph::edgeAlreadyExist (Edge e);//Edge e �� �׷����� �̹� �����ϸ� TRUE, �ƴϸ� FALSE�� return�Ѵ�.
	bool Graph::insertEdge (Edge e);//Edge e�� �׷����� �����Ѵ�.Edge e�� �̹� �����Ͽ� ������ �� ������ FALSE, �������� �ʾ� ���������� ���ԵǸ� TRUE�� ��´�.
	void Graph::showGraph ();//���� ������ �׷����� ����Ͽ� �����ش�
} ;