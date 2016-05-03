#include "Graph.h"
Graph::Graph (int numOfVertices, int numOfEdges)
{
	Vertex v, w ;
	this->numOfVertices = numOfVertices ;
	this->numOfEdges = numOfEdges ;
	this->adjacency = new Cost * [numOfVertices] ;
	for ( v = 0 ; v < numOfVertices ; v++ )
		this->adjacency[v] = new Cost [numOfVertices] ;
	
	for ( v = 0 ; v < numOfVertices ; v++ )
		for ( w = 0 ; w < numOfVertices ; w++ )
			this->adjacency[v][w] = -1 ;
}

Graph::~Graph ()
{
	for ( int i = 0 ; i < this->numOfVertices ; i ++ )
		delete this->adjacency[i] ;
		delete this->adjacency ;
}

bool Graph::edgeAlreadyExist (Edge e)
{
	if(e.fromV<0 || e.toV<0)
	{
		return false;
	}
	return (this->adjacency[e.fromV][e.toV] > -1 ) ;
}
bool Graph::insertEdge (Edge e)
{
	// Undirected graph 이므로, 대칭되는 edge도 함께 삽입한다.
	if((e.fromV<0)||(e.fromV>=this->numOfVertices))
	{
		printf("%s\n", MCST_MSG_Error_FirstVertex);
		return false;
	}
	else if((e.toV<0)||(e.toV>=this->numOfVertices))
	{
		printf("%s\n", MCST_MSG_Error_SecondVertex);
		return false;
	}
	else if(e.cost<1)
	{
		printf("%s\n", MCST_MSG_Error_Cost);
		return false;
	}
	this->adjacency[e.fromV][e.toV] = e.cost ;
	this->adjacency[e.toV][e.fromV] = e.cost ;

	return true;
}

void Graph::showGraph ()
{
	int i=0, j=0;
	printf("\n%s",MCST_MSG_showHead);
	while(i<this->numOfVertices)
	{
		printf("\n[%d] -> ", i);
		j=0;
		while(j<this->numOfVertices)
		{
			if(this->adjacency[i][j]!=-1)
			{
				printf("%d(%d)  ", j, this->adjacency[i][j]);
			}
			j++;
		}
		i++;
	}
				
// 출력 화면을 보고 작성할 것
// cost가 -1인 edge는 존재하지 않는 것이므로 출력하지 않는다.

}

int Graph::getnumOfVertices()
{
	return this->numOfVertices;
}