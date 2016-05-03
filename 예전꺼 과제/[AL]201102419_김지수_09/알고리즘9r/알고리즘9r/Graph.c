#include "Graph.h"


Graph * Graph_new (int numOfVertices)
{
	Graph * temp=NewObject(Graph);
	int v, w, i;

	temp->numOfVertices=numOfVertices;
	temp->adjacency = NewVector(int*, temp->numOfVertices);

	for (i=0; i < temp->numOfVertices; i++) 
	{
		temp->adjacency[i] = NewVector(int,temp->numOfVertices);
	}

	for ( v = 0 ; v < numOfVertices ; v++ )
		for ( w = 0 ; w < numOfVertices ; w++ )
			temp->adjacency[v][w] = -1 ;

	return temp;
	//주어진 vertex 수 만큼을 갖는 Graph 초기 객체를 생성
//edge는 나중에 추가

}
void Graph_free (Graph * _this)
{//그래프 객체를 소멸시킨다.


}
Bool Graph_isVertexValid (Graph * _this, Vertex v)
{
	if((v>=0)&&(v<_this->numOfVertices))
	{
		
		return T;
	}
	printf("Vertex오류\n");
	return F;
	//주어진 vertex v가 valid한지 판단
//0보다 크거나 같고, _this->numOfVertices보다 작으면 TRUE, 아니면 FALSE를 얻는다.
}
Bool Graph_isEdgeValid (Graph * _this, Edge e) 
{
	if(Graph_isVertexValid(_this, e.fromV)&&Graph_isVertexValid(_this, e.toV)&&(e.fromV!=e.toV))
	{
		
		return T;
	}
	if(e.fromV==e.toV)
	{
		printf("self-loop!\n");
	}
	return F;

	//주어진 edge e가 valid한지 판단
//Edge의 각각의 vertex가 valid하고, self-loop이 아니어야 한다

}
Bool Graph_doesEdgeAlreadyExist (Graph * _this, Edge e) 
{
	
	if(_this->adjacency[e.fromV][e.toV] > -1 )
	{
		return T;
	}
	return F;
	
	//그래프에 Edge e가 존재하는지를 검사한다.
//이 함수는 Coloring_inputNewEdge()에서 사용된다.

}
Bool Graph_insertEdge (Graph * _this, Edge e) 
{//주어진 Edge e를 그래프에 삽입한다.
//정상적으로 삽입되었으면 TRUE, 아니면 FALSE 를 얻는다.
	if((e.fromV<0)||(e.fromV>=_this->numOfVertices))
	{
		
		return F;
	}
	else if((e.toV<0)||(e.toV>=_this->numOfVertices))
	{
		
		return F;
	}
	
	_this->adjacency[e.fromV][e.toV] = e.toV ;
	_this->adjacency[e.toV][e.fromV] = e.fromV ;

	return T;
}
int Graph_numOfVertices(Graph * _this)
{
	return _this->numOfVertices;
}