#pragma once
#include "Global.h"

typedef Vertex SetMember ;
typedef SetMember SetID ;

class PWDisjointSets
{
private:
	int size ;
// number of total members in the overall sets
// 이번 실습 문제에서는 그래프의 vertex 수가 된다.
	SetMember * parent ;
// array for the sets
// 객체 생성할 때, 주어진 size의 크기만큼 동적으로 만든다.

public:
	PWDisjointSets::PWDisjointSets (int size);
	PWDisjointSets::~PWDisjointSets ();
	SetID PWDisjointSets::find (SetMember member);//주어진 member 가 어느 집합에 속해 있는지, 그 집합의 ID를 얻는다.
	void PWDisjointSets::unionOfDisjointSets (SetID id1, SetID id2);
} ;