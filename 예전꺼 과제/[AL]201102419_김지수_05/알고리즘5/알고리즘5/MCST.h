#pragma once
#include "Global.h"
#include "Graph.h"
#include "List.h"
#include "MinPriorityQ.h"
#include "ListIter.h"
#include "PWDisjointSets.h"

class MCST 
{
	private:
	Graph * graph ;
// MCST를 찾으려는 그래프
	MinPriorityQ * edgeMinPriorityQ;
// Edge들을 cost가 작은 순서로 얻기 위해서 사용한다.
// Edge가 입력될 때마다 Priority Queue 에 삽입한다.
	List * treeEdges ;
	
// MCST로서 찾아진 tree edge들을 보관한다.
	static char * msg_Starting ;
	static char * msg_Ending ;
	static char * msg_Fail ;
	
	
// 이와 같이 모든 메시지는 여기에...
public:
	MCST::MCST ();
	MCST::~MCST ();
	void MCST::showMSG_Starting ();
	void MCST::showMSG_Ending ();
	void MCST::showMSG_Fail();//MCST를 찾지 못했을 경우를 위한 출력을 한다.
	void MCST::inputGraph ();//키보드로부터 그래프 정보를 입력 받는다. 마지막에 입력된 그래프를 출력하여 보여준다.
	bool MCST::findMCST ();//MCST를 찾아준다.
	void MCST::showResult ();//찾아진 MCST의 edge들을 출력한다.
	void MCST::printMSG_Error_EdgeAlreadyExist();
	void MCST::showMSG_EdgeDiscarded();
	void MCST::showMSG_EdgeAdded();
	int MCST::inputNumOfVertices();
	int MCST::inputNumOfEdges();
	Edge MCST::inputEdge();

} ;
