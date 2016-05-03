#pragma once
#include "Global.h"
#include "VertexAndEdge.h"

typedef struct _Graph Graph;

struct _Graph {
int numOfVertices ;
int numOfEdges ;
int ** adjacency ;
} ; // Adjacency matrix로 구현한 경우


Graph * Graph_new (int numOfVertices) ;//주어진 vertex 수 만큼을 갖는 Graph 초기 객체를 생성
//edge는 나중에 추가
void Graph_free (Graph * _this) ;//그래프 객체를 소멸시킨다.
Bool Graph_isVertexValid (Graph * _this, Vertex v) ;//주어진 vertex v가 valid한지 판단
//0보다 크거나 같고, _this->numOfVertices보다 작으면 TRUE, 아니면 FALSE를 얻는다.
Bool Graph_isEdgeValid (Graph * _this, Edge e) ;//주어진 edge e가 valid한지 판단
//Edge의 각각의 vertex가 valid하고, self-loop이 아니어야 한다
Bool Graph_doesEdgeAlreadyExist (Graph * _this, Edge e) ;//그래프에 Edge e가 존재하는지를 검사한다.
//이 함수는 Coloring_inputNewEdge()에서 사용된다.
Bool Graph_insertEdge (Graph * _this, Edge e) ;//주어진 Edge e를 그래프에 삽입한다.
//정상적으로 삽입되었으면 TRUE, 아니면 FALSE 를 얻는다.
int Graph_numOfVertices(Graph * _this);