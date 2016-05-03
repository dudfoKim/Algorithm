#pragma once
#include "Global.h"
#include "List.h"

class Iter
{
	private:
	List * list ; // �˻��ؾ� �� ����Ʈ
	int currentLocation ; //���� (���) ��ġ
	public:
	Iter::Iter (List * list);
	Iter::~Iter ();
	void Iter::begin ();
	bool Iter::endOfList ();
	int Iter::currentElement ();
	void Iter::next ();

} ;