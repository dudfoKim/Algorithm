#pragma once
#include "Global.h"
#include "MCST_MSG.h"

class Graph
{
private:
	int numOfVertices ;
	int numOfEdges ;
	Cost ** adjacency ; // 이차원 배열
public:
	Graph::Graph (int numOfVertices, int numOfEdges);
	Graph::~Graph ();
	int Graph::getnumOfVertices();//그래프의 vertex 수를 알려준다.
	bool Graph::edgeAlreadyExist (Edge e);//Edge e 가 그래프에 이미 존재하면 TRUE, 아니면 FALSE를 return한다.
	bool Graph::insertEdge (Edge e);//Edge e를 그래프에 삽입한다.Edge e가 이미 존재하여 삽입할 수 없으면 FALSE, 존재하지 않아 정상적으로 삽입되면 TRUE를 얻는다.
	void Graph::showGraph ();//현재 상태의 그래프를 출력하여 보여준다
} ;