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
	//�־��� vertex �� ��ŭ�� ���� Graph �ʱ� ��ü�� ����
//edge�� ���߿� �߰�

}
void Graph_free (Graph * _this)
{//�׷��� ��ü�� �Ҹ��Ų��.


}
Bool Graph_isVertexValid (Graph * _this, Vertex v)
{
	if((v>=0)&&(v<_this->numOfVertices))
	{
		
		return T;
	}
	printf("Vertex����\n");
	return F;
	//�־��� vertex v�� valid���� �Ǵ�
//0���� ũ�ų� ����, _this->numOfVertices���� ������ TRUE, �ƴϸ� FALSE�� ��´�.
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

	//�־��� edge e�� valid���� �Ǵ�
//Edge�� ������ vertex�� valid�ϰ�, self-loop�� �ƴϾ�� �Ѵ�

}
Bool Graph_doesEdgeAlreadyExist (Graph * _this, Edge e) 
{
	
	if(_this->adjacency[e.fromV][e.toV] > -1 )
	{
		return T;
	}
	return F;
	
	//�׷����� Edge e�� �����ϴ����� �˻��Ѵ�.
//�� �Լ��� Coloring_inputNewEdge()���� ���ȴ�.

}
Bool Graph_insertEdge (Graph * _this, Edge e) 
{//�־��� Edge e�� �׷����� �����Ѵ�.
//���������� ���ԵǾ����� TRUE, �ƴϸ� FALSE �� ��´�.
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