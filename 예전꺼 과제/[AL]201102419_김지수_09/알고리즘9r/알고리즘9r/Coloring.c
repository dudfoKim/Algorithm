#include "Coloring.h"

void Coloring_inputNumOfVertices (Coloring * _this) ;
void Coloring_inputNumOfEdges (Coloring * _this) ;
Edge Coloring_inputNewEdge (Coloring * _this);



Coloring * Coloring_new ()
// Coloring ��ü�� �����ϰ�, �־��� graph�� Coloring �� �غ� �Ѵ�.
{
	Coloring * _this = NewObject(Coloring) ; //��ü����
	_this->graph = NULL ;
	// �׷����� �Է� �ޱ� ������ NULL�� ����
	// �׷��� ��ü�� Coloring_inputAndMakeGraph()���� �����ȴ�
	_this->color = NULL ;
	// �׷����� �Է� �ޱ� ������ Color Vector �� NULL �� �ʱ�ȭ
	// color[] �迭�� Coloring_runColoring()���� �����ȴ�
	_this->startingVertex = 0 ; // �ƹ� vertex������ ��� ����
	_this->sameColorEdges = EdgeList_new () ;
	
	return _this ; // ��ü�� pointer�� return
} // end of Coloring_new ()

void Coloring_free (Coloring * _this)
{
	
	free(_this->graph);
	free(_this->color);
	free(_this->sameColorEdges);
	free(_this);
}

void Coloring_inputAndMakeGraph (Coloring * _this)
//Coloring ��ü�� �����ϰ�, �־��� graph�� Coloring �� �غ� �Ѵ�.
{
	Edge e ;
	int edgeInputCount ;
	Coloring_inputNumOfVertices (_this) ;
	Coloring_inputNumOfEdges (_this) ;
	_this->graph = Graph_new (_this->numOfVertices) ;
	e = Coloring_inputNewEdge (_this) ;
	edgeInputCount = 1;

	if(e.fromV==-1&&e.toV-1)
	{
		printf("Edge�Է� ����!edge�� ������ 1���� �����մϴ�.\n");
		_this->numOfEdges=1;
	}

	
	while (edgeInputCount < _this->numOfEdges) 
	{
		
		if (! Graph_insertEdge (_this->graph, e)) 
		{
			printf("Error: Edge (%d,%d)�� �Է��� �����Ͽ����ϴ�.\n", e.fromV, e.toV) ;
		} 
		else 
		{
			edgeInputCount++ ;
		}
		
		
		
		e = Coloring_inputNewEdge (_this) ;

		if(e.fromV==-1&&e.toV-1)
		{
			printf("Edge�Է� ����!edge�� ������ %d���� �����մϴ�.\n", edgeInputCount-1);
			_this->numOfEdges=edgeInputCount-1;
		}
	}
	if (! Graph_insertEdge (_this->graph, e)) 
	{
		printf("Error: Edge (%d,%d)�� �Է��� �����Ͽ����ϴ�.\n", e.fromV, e.toV) ;
	} 
} // end of Coloring_inputAndMakeGraph()

void Coloring_showGraph (Coloring * _this)
// �Էµ� graph�� ����Ͽ� ���� �ش�.
{
	Vertex fromVertex, toVertex ;
	AdjacentVerticesIterator * iter = AdjacentVerticesIterator_new (_this->graph) ;
	printf("<Coloring�� ���� �׷���>\n") ;
	for (fromVertex = 0 ; fromVertex<Graph_numOfVertices(_this->graph) ; fromVertex ++)
	{
		printf("[%d]", fromVertex) ;
		AdjacentVerticesIterator_begin (iter, fromVertex) ;
		
		while (! AdjacentVerticesIterator_end (iter) )
		{
			toVertex = AdjacentVerticesIterator_currentElement (iter) ;
			if(toVertex!=-1)
			{
				printf(" -> %d", toVertex) ;
			}
			AdjacentVerticesIterator_next (iter);
		}
		
		printf("\n") ;
	}
	//AdjacentVerticesIterator_free(iter);
} // end of Coloring_showGraph ()

void Coloring_runColoring (Coloring * _this)
{
	//Coloring�� ����
	//�׷����� breadth-first search: queue�� ���
	Vertex fromVertex, toVertex, v ;
	Color toVertexColor ;
	AdjacentVerticesIterator * iter ;
	VertexQueue * bfsQ;
	int numOfVertices = Graph_numOfVertices(_this->graph) ;
	
	

	_this->color = NewVector(Color,_this->numOfVertices ); //�Ҹ��� Coloring_free()����
	
	for ( v = 0 ; v < numOfVertices ; v++)
	{
		_this->color[v] =NONE ;
	}
	
	_this->color[_this->startingVertex] = RED ; // ��� vertex�� color�� RED�� ��
	iter = AdjacentVerticesIterator_new(_this->graph) ; // �Ҹ��� �� �Լ� ���� ����
	bfsQ = VertexQueue_new() ; // �Ҹ��� �� �Լ� ���� ����
	
	VertexQ_add (bfsQ, _this->startingVertex) ;
	
	while (! VertexQueue_isEmpty(bfsQ) )
	{
		fromVertex = VertexQueue_delete (bfsQ);
	
		toVertexColor = ((_this->color[fromVertex])== RED) ? BLUE : RED ;
		
		AdjacentVerticesIterator_begin (iter, fromVertex) ;
		
		while ( ! AdjacentVerticesIterator_end (iter) ) 
		{
			
			toVertex= AdjacentVerticesIterator_currentElement (iter) ;
			
			if (_this->color[toVertex] == NONE) 
			{
				_this->color[toVertex] = toVertexColor ;
				
				VertexQ_add (bfsQ, toVertex) ;
			
			}
			
			AdjacentVerticesIterator_next (iter) ;
		}
	}
	
	VertexQueue_free (bfsQ) ;
	//AdjacentVerticesIterator_free (iter) ;

}

void Coloring_showColoring (Coloring * _this)
{
	int v = Graph_numOfVertices(_this->graph) ;
	int i=0;

	EdgeListIterator * iter;

	printf("\nRED vertices : ");

	while(i<v)
	{
		if(_this->color[i]==1)
		{
			printf("%d ", i);
		}
		i++;
	}
	i=0;
	printf("\nBLUE vertices : ");
	
	while(i<v)
	{
		if(_this->color[i]==2)
		{
			printf("%d ", i);
		}
		i++;
	}

	printf("\nVertices with no color : ");
	i=0;

	while(i<v)
	{
		if(_this->color[i]==0)
		{
			printf("%d ", i);
		}
		i++;
	}

	printf("\n\t->����� �׷����� �ƴմϴ�.\n");


	Coloring_checkColors (_this);

	

	if(_this->sameColorEdges->length!=0)
	{
		
		printf("�� ���� ���� edge�� �ֽ��ϴ�. : ");

		while(_this->sameColorEdges->head!=NULL)
		{
			printf("(%d, %d) ", _this->sameColorEdges->head->e.fromV, _this->sameColorEdges->head->e.toV);
			_this->sameColorEdges->head=_this->sameColorEdges->head->next;
		}
		/*iter = EdgeListIterator_new(_this->sameColorEdges);
		EdgeListIterator_begin(iter);
		
		while(!)
		{
			printf("(%d, %d) ", EdgeListIterator_currentElement(iter).fromV, EdgeListIterator_currentElement(iter).toV);
			EdgeListIterator_next(iter);
		}
		EdgeListIterator_free(iter);*/
	}
		
	else
	{
		printf("�� ���� ���� edge�� �����ϴ�. ");
	}
	

	
	//Vertex�� Color�� ���: coloring_showVertexColors() ���
	//RED vertices: 0
	//BLUE vertices: 1, 2, 3
	//Vertices with no color: 4
	//->����� �׷����� �ƴմϴ�.
	//�� ���� ���� edge���� ����Ʈ sameColorEdges�� �����: Coloring_checkColors()�� ���
	//sameColorEdges�� ������ ����Ѵ�: Coloring_showSameColorEdges()�� ���
	//�� ���� ���� edge�� �ֽ��ϴ�: (2, 3)
}

void Coloring_inputNumOfVertices (Coloring * _this) 
{
	int input=-1;

	while(input<0)
	{
		printf("Vertice�� ������ �Է��Ͻÿ�. : ");
		scanf("%d", &input);
	}

	_this->numOfVertices=input;

	
	//0 ���� ū vertex ���� �Է� �޴´�.
	//�߸� �ԷµǾ��� ��� �ٽ� �Է� �޴´�.
}

void Coloring_inputNumOfEdges (Coloring * _this)
{
	
	int input=-1;

	while(input<0)
	{
		printf("Edge�� ������ �Է��Ͻÿ�. : ");
		scanf("%d", &input);
	}

	_this->numOfEdges=input;
	//0 ���� ū edge ���� �Է� �޴´�.
	//0�̸� edge�� ���� �׷����̾, coloring�� �����ϱ⿡ �������� �ʴ�. �ٽ� �Է� �޴´�.
	//0���� ���ų� �۾Ƽ�, �߸� �ԷµǾ��� ��� �ٽ� �Է� �޴´�.
}

Edge Coloring_inputNewEdge (Coloring * _this)
{
	Edge input;
	int reinput=1;
	
	while(reinput)
	{
		printf("Edge�� �Է��ϼ��� from to : ");
		scanf("%d %d", &input.fromV, &input.toV);

		if(input.fromV==-1&&input.toV==-1)
		{
			return input;
		}

		if(Graph_isEdgeValid(_this->graph, input))
		{
			reinput=0;
		}

		if(Graph_doesEdgeAlreadyExist(_this->graph, input))
		{
			printf("�̹� �����ϴ� Edge�Դϴ�!\n");
			reinput=1;
		}
	}

	return input;
	//�ܺηκ��� �ϳ��� ���ο� edge�� �Է� �޾�, �� edge�� ��´�.
	//�������� edge�� ��쿡�� �Էµ� edge�� ��´�.
	//<-1,-1>�� �ԷµǸ�, edge �Է��� ���� �˸��� �������� edge�� �����Ѵ�.
	//Vertex ���� �˻縦 �ϰ�, �̻��� ������ �ٽ� �Է� �޴´�.
	//Graph_isVertexValid() ���
	//(v,v)�� ���� Self-loop edge�� �����޽����� �������� �ٽ� �Է� �޴´�.
	//Graph_isEdgeValid() ���
	//�׷����� ���� edge �ߺ� �˻縦 �Ͽ�, ���ο� edge�� �ƴϸ� �ٽ� �Է� �޴´�.
	//Graph_doesEdgeAlreadyExist() ���
	//�� �Լ��� Coloring_inputAndMake()���� ���ȴ�.
}

void Coloring_checkColors (Coloring * _this)
{
	Edge e ;
	int numOfVertices = Graph_numOfVertices (_this->graph);

	
	AdjacentVerticesIterator * iter = AdjacentVerticesIterator_new (_this->graph) ;
	
	
	for ( e.fromV = 0 ; e.fromV < numOfVertices ; e.fromV++ ) 
	{
		AdjacentVerticesIterator_begin (iter, e.fromV) ;
		
		while ( ! AdjacentVerticesIterator_end (iter) ) 
		{
			
			e.toV = AdjacentVerticesIterator_currentElement (iter) ;
				
			if(e.toV!=-1)
			{
				if ( _this->color[e.fromV] == _this->color[e.toV] )
				{
					
					EdgeList_add (_this->sameColorEdges, e) ;
				}
			}
				
			AdjacentVerticesIterator_next (iter) ;
		}
	}
	AdjacentVerticesIterator_free(iter) ;
}