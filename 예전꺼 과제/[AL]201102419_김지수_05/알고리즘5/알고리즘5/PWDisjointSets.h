#pragma once
#include "Global.h"

typedef Vertex SetMember ;
typedef SetMember SetID ;

class PWDisjointSets
{
private:
	int size ;
// number of total members in the overall sets
// �̹� �ǽ� ���������� �׷����� vertex ���� �ȴ�.
	SetMember * parent ;
// array for the sets
// ��ü ������ ��, �־��� size�� ũ�⸸ŭ �������� �����.

public:
	PWDisjointSets::PWDisjointSets (int size);
	PWDisjointSets::~PWDisjointSets ();
	SetID PWDisjointSets::find (SetMember member);//�־��� member �� ��� ���տ� ���� �ִ���, �� ������ ID�� ��´�.
	void PWDisjointSets::unionOfDisjointSets (SetID id1, SetID id2);
} ;