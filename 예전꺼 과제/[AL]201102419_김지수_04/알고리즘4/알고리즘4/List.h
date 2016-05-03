#pragma once
#include "Global.h"

class List {
	friend class Iter ;
	private:
	int maxLength ; // �迭 body[]�� ũ��
	int length ; // ����Ʈ�� ��� �ִ� ������ ����
	Element * body ; // ���� ����Ʈ�� ���ҵ��� �迭
// ��� ���Ҵ� ������ body[0]���� ���ʷ� ä���� �ְ� �����Ѵ�.
	public:
	List::List (int MaxSize);
	List::~List ();
	void List::reset ();
	bool List::isFull ();
	bool List::isEmpty ();
	bool List::isIndexOK (int index);
	bool List::doesExist (Element e);
	int List::Length();
	void List::insert (Element e);
	Element List::deleteKth (int K);
	Element List::deleteMin ();
	Element List::deleteMax ();

};