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
// MCST�� ã������ �׷���
	MinPriorityQ * edgeMinPriorityQ;
// Edge���� cost�� ���� ������ ��� ���ؼ� ����Ѵ�.
// Edge�� �Էµ� ������ Priority Queue �� �����Ѵ�.
	List * treeEdges ;
	
// MCST�μ� ã���� tree edge���� �����Ѵ�.
	static char * msg_Starting ;
	static char * msg_Ending ;
	static char * msg_Fail ;
	
	
// �̿� ���� ��� �޽����� ���⿡...
public:
	MCST::MCST ();
	MCST::~MCST ();
	void MCST::showMSG_Starting ();
	void MCST::showMSG_Ending ();
	void MCST::showMSG_Fail();//MCST�� ã�� ������ ��츦 ���� ����� �Ѵ�.
	void MCST::inputGraph ();//Ű����κ��� �׷��� ������ �Է� �޴´�. �������� �Էµ� �׷����� ����Ͽ� �����ش�.
	bool MCST::findMCST ();//MCST�� ã���ش�.
	void MCST::showResult ();//ã���� MCST�� edge���� ����Ѵ�.
	void MCST::printMSG_Error_EdgeAlreadyExist();
	void MCST::showMSG_EdgeDiscarded();
	void MCST::showMSG_EdgeAdded();
	int MCST::inputNumOfVertices();
	int MCST::inputNumOfEdges();
	Edge MCST::inputEdge();

} ;
