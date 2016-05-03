#include "MCST.h"
#include "MCST_MSG.h"

char * MCST::msg_Starting = MCST_MSG_Starting ;
char * MCST::msg_Ending = MCST_MSG_Ending ;

MCST::MCST ()
{
this->graph = 0 ;
this-> edgeMinPriorityQ = 0 ;
this-> treeEdges= 0 ;
}
MCST::~MCST ()
{
delete this->treeEdges ;
delete this->edgeMinPriorityQ ;
delete this->graph ;
}

void MCST::showMSG_Starting ()
{
printf ("%s\n", this->msg_Starting) ;
}
void MCST::showMSG_Ending ()
{
printf ("\n%s", this->msg_Ending) ;
}

void MCST::printMSG_Error_EdgeAlreadyExist()
{
	printf("%s\n", MCST_MSG_Error_EdgeAlreadyExist);
}
void MCST::showMSG_EdgeDiscarded()
{
	printf("%s", MCST_MSG_EdgeDiscarded);
}
void MCST::showMSG_EdgeAdded()
{
	printf("%s", MCST_MSG_EdgeAdded);
}
void MCST::inputGraph ()
{
	int numOfVertices ;
	int numOfEdges ;
	Edge e ;
	int edgeCount ;
	
	printf("\n%s", MCST_MSG_Notice);

	numOfVertices = this->inputNumOfVertices() ;
	numOfEdges = this->inputNumOfEdges() ;
	this->graph = new Graph(numOfVertices, numOfEdges) ;
	// Vertex의 수와 edge의 수가 주어지면,
	// 이때 그래프의 객체가 실체화 된다.
	this->edgeMinPriorityQ = new MinPriorityQ (numOfEdges) ;
	this->treeEdges = new List (numOfVertices-1) ;
	edgeCount = 0 ;
	
	printf("\n%s %d %s\n %s\n", MCST_MSG_StartingInputEdge1, numOfEdges, MCST_MSG_StartingInputEdge2 ,  MCST_MSG_StartingInputEdge3);

	while ( edgeCount < numOfEdges )
	{
		e = this->inputEdge() ;
		if ( this->graph->edgeAlreadyExist(e) )
		{
			this->printMSG_Error_EdgeAlreadyExist() ;
		}
		else
		{
			if(this->graph->insertEdge(e))
			{
				this->edgeMinPriorityQ->insert(e) ;
				edgeCount ++ ;
			}
		}
	}
	this->graph->showGraph() ;
}

bool MCST::findMCST ()
{
	PWDisjointSets * vertexSets;
	SetID set_fromV, set_toV ;
	Edge e ;
	int numOfVertices = this->graph->getnumOfVertices() ;
	int maxTreeEdges = numOfVertices - 1 ;
	vertexSets = new PWDisjointSets(numOfVertices) ;
	
	printf("\n%s", MCST_MSG_StartSearch);

	while ( ((this->treeEdges->getsize()) < maxTreeEdges) && (! this->edgeMinPriorityQ->isEmpty()) )
	{
		e = this->edgeMinPriorityQ->deleteMin() ;
		set_fromV = vertexSets->find(e.fromV) ;
		set_toV = vertexSets->find(e.toV) ;
		if (set_fromV == set_toV) 
		{
			// Edge e creates a cycle in the tree
			// Discard the edge: No Action for discarding.
			printf("\nEdge = (%d, %d, (%d)) : ", e.fromV, e.toV, e.cost);
			this->showMSG_EdgeDiscarded() ;
		}
		else 
		{
			// e does not create a cycle in the tree
			vertexSets->unionOfDisjointSets(set_fromV, set_toV) ;
			this->treeEdges->insert(e) ;
			printf("\nEdge = (%d, %d, (%d)) : ", e.fromV, e.toV, e.cost);
			this->showMSG_EdgeAdded() ;
		}
	}
	
	delete vertexSets ;
	
	return (this->treeEdges->getsize()== (maxTreeEdges) ) ;
	// 찾아진 tree edge의 수는 vertex 수보다 하나 작은 수이어야, 성공한 것이다.
}

void MCST::showResult ()
{
	int numOfVertices ;
	Edge e ;
	ListIter * iter ;
	printf("\n\n%s", MCST_MSG_ResultHead) ; //
	iter = new ListIter(treeEdges) ;
	iter->begin() ;
	while ( ! iter->endOfList() ) 
	{
		e = iter->getElement() ;
		printf("\n(%d, %d, (%d))",e.fromV, e.toV, e.cost) ; // 출력 화면을 보고 작성할 것.
		iter->next() ;
	}
	delete iter ;
}

int MCST::inputNumOfVertices()
{
	int a;
	printf("\n%s",MCST_MSG_GetNumOfVertices);
	scanf("%d", &a);
	return a;
}

int MCST::inputNumOfEdges()
{
	int a;
	printf("%s",MCST_MSG_GetNumOfEdges);
	scanf("%d", &a);
	return a;
}

Edge MCST::inputEdge()
{
	Edge a;
	printf("%s", MCST_MSG_InputEdge);
	scanf("%d %d %d", &a.fromV, &a.toV, &a.cost);
	return a;
}