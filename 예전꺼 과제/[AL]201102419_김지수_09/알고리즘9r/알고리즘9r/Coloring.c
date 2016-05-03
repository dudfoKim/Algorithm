#include "Coloring.h"

void Coloring_inputNumOfVertices (Coloring * _this) ;
void Coloring_inputNumOfEdges (Coloring * _this) ;
Edge Coloring_inputNewEdge (Coloring * _this);



Coloring * Coloring_new ()
// Coloring 객체를 생성하고, 주어진 graph로 Coloring 할 준비를 한다.
{
	Coloring * _this = NewObject(Coloring) ; //객체생성
	_this->graph = NULL ;
	// 그래프를 입력 받기 전까지 NULL로 설정
	// 그래프 객체는 Coloring_inputAndMakeGraph()에서 생성된다
	_this->color = NULL ;
	// 그래프를 입력 받기 전까지 Color Vector 를 NULL 로 초기화
	// color[] 배열은 Coloring_runColoring()에서 생성된다
	_this->startingVertex = 0 ; // 아무 vertex에서나 출발 가능
	_this->sameColorEdges = EdgeList_new () ;
	
	return _this ; // 객체의 pointer를 return
} // end of Coloring_new ()

void Coloring_free (Coloring * _this)
{
	
	free(_this->graph);
	free(_this->color);
	free(_this->sameColorEdges);
	free(_this);
}

void Coloring_inputAndMakeGraph (Coloring * _this)
//Coloring 객체를 생성하고, 주어진 graph로 Coloring 할 준비를 한다.
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
		printf("Edge입력 종료!edge의 갯수를 1개로 변경합니다.\n");
		_this->numOfEdges=1;
	}

	
	while (edgeInputCount < _this->numOfEdges) 
	{
		
		if (! Graph_insertEdge (_this->graph, e)) 
		{
			printf("Error: Edge (%d,%d)의 입력이 실패하였습니다.\n", e.fromV, e.toV) ;
		} 
		else 
		{
			edgeInputCount++ ;
		}
		
		
		
		e = Coloring_inputNewEdge (_this) ;

		if(e.fromV==-1&&e.toV-1)
		{
			printf("Edge입력 종료!edge의 갯수를 %d개로 변경합니다.\n", edgeInputCount-1);
			_this->numOfEdges=edgeInputCount-1;
		}
	}
	if (! Graph_insertEdge (_this->graph, e)) 
	{
		printf("Error: Edge (%d,%d)의 입력이 실패하였습니다.\n", e.fromV, e.toV) ;
	} 
} // end of Coloring_inputAndMakeGraph()

void Coloring_showGraph (Coloring * _this)
// 입력된 graph를 출력하여 보여 준다.
{
	Vertex fromVertex, toVertex ;
	AdjacentVerticesIterator * iter = AdjacentVerticesIterator_new (_this->graph) ;
	printf("<Coloring을 위한 그래프>\n") ;
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
	//Coloring을 실행
	//그래프의 breadth-first search: queue를 사용
	Vertex fromVertex, toVertex, v ;
	Color toVertexColor ;
	AdjacentVerticesIterator * iter ;
	VertexQueue * bfsQ;
	int numOfVertices = Graph_numOfVertices(_this->graph) ;
	
	

	_this->color = NewVector(Color,_this->numOfVertices ); //소멸은 Coloring_free()에서
	
	for ( v = 0 ; v < numOfVertices ; v++)
	{
		_this->color[v] =NONE ;
	}
	
	_this->color[_this->startingVertex] = RED ; // 출발 vertex의 color는 RED로 함
	iter = AdjacentVerticesIterator_new(_this->graph) ; // 소멸은 이 함수 종료 전에
	bfsQ = VertexQueue_new() ; // 소멸은 이 함수 종료 전에
	
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

	printf("\n\t->연결된 그래프가 아닙니다.\n");


	Coloring_checkColors (_this);

	

	if(_this->sameColorEdges->length!=0)
	{
		
		printf("끝 색이 같은 edge가 있습니다. : ");

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
		printf("끝 색이 같은 edge가 없습니다. ");
	}
	

	
	//Vertex의 Color를 출력: coloring_showVertexColors() 사용
	//RED vertices: 0
	//BLUE vertices: 1, 2, 3
	//Vertices with no color: 4
	//->연결된 그래프가 아닙니다.
	//끝 색이 같은 edge들의 리스트 sameColorEdges를 만든다: Coloring_checkColors()를 사용
	//sameColorEdges의 내용을 출력한다: Coloring_showSameColorEdges()를 사용
	//끝 색이 같은 edge가 있습니다: (2, 3)
}

void Coloring_inputNumOfVertices (Coloring * _this) 
{
	int input=-1;

	while(input<0)
	{
		printf("Vertice의 개수를 입력하시오. : ");
		scanf("%d", &input);
	}

	_this->numOfVertices=input;

	
	//0 보다 큰 vertex 수를 입력 받는다.
	//잘못 입력되었을 경우 다시 입력 받는다.
}

void Coloring_inputNumOfEdges (Coloring * _this)
{
	
	int input=-1;

	while(input<0)
	{
		printf("Edge의 개수를 입력하시오. : ");
		scanf("%d", &input);
	}

	_this->numOfEdges=input;
	//0 보다 큰 edge 수를 입력 받는다.
	//0이면 edge가 없는 그래프이어서, coloring을 적용하기에 적합하지 않다. 다시 입력 받는다.
	//0보다 같거나 작아서, 잘못 입력되었을 경우 다시 입력 받는다.
}

Edge Coloring_inputNewEdge (Coloring * _this)
{
	Edge input;
	int reinput=1;
	
	while(reinput)
	{
		printf("Edge를 입력하세요 from to : ");
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
			printf("이미 존재하는 Edge입니다!\n");
			reinput=1;
		}
	}

	return input;
	//외부로부터 하나의 새로운 edge를 입력 받아, 그 edge를 얻는다.
	//정상적인 edge인 경우에는 입력된 edge를 얻는다.
	//<-1,-1>이 입력되면, edge 입력의 끝을 알리는 정상적인 edge로 간주한다.
	//Vertex 오류 검사를 하고, 이상이 있으면 다시 입력 받는다.
	//Graph_isVertexValid() 사용
	//(v,v)와 같은 Self-loop edge는 오류메시지를 내보내고 다시 입력 받는다.
	//Graph_isEdgeValid() 사용
	//그래프에 대해 edge 중복 검사를 하여, 새로운 edge가 아니면 다시 입력 받는다.
	//Graph_doesEdgeAlreadyExist() 사용
	//이 함수는 Coloring_inputAndMake()에서 사용된다.
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