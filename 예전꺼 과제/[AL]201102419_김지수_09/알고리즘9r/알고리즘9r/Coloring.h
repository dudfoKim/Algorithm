#pragma once
#include "Global.h"
#include "Graph.h"
#include "EdgeList.h"
#include "VertexAndEdge.h"
#include "AdjacentVerticesIterator.h"
#include "VertexQueue.h"
#include "Graph.h"
#include "EdgeListIterator.h"

typedef struct _Coloring Coloring ;
typedef enum {NONE, RED, BLUE} Color ;

struct _Coloring 
{
	int numOfVertices ;
	int numOfEdges ;
	Graph * graph ;
	Color * color ; // 각 vertex의 color를 저장할 배열
	Vertex startingVertex ;
	EdgeList * sameColorEdges ; // 끝 색이 같은 edge들의 리스트
} ;

Coloring * Coloring_new () ;//Coloring 객체를 생성한다.
void Coloring_free (Coloring * _this) ;//객체를 소멸시킨다.
//먼저, _this 가 소유하고 있는 (즉, member variable로 선언된) 모든 객체
//마지막으로, _this 객체 자체
void Coloring_inputAndMakeGraph (Coloring * _this) ;//외부로부터 vertex와 edge들을 입력 받아 그래프를 만든다.
//Vertex는 최소한 1 개 이상 존재해야 한다.
//Edge는 1개 또는 그 이상 존재해야 한다.
void Coloring_showGraph (Coloring * _this) ;//현재 가지고 있는 그래프를 보여준다.
void Coloring_runColoring (Coloring * _this) ;//Coloring를 실행한다.
void Coloring_showColoring (Coloring * _this) ;//Coloring 결과를 보여준다.
void Coloring_checkColors (Coloring * _this);