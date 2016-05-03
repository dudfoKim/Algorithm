#include "PWDisjointSets.h"

PWDisjointSets::PWDisjointSets (int numOfMembers)
{
	this->size = numOfMembers ;
	this->parent = new SetMember [numOfMembers] ;
	for (int i = 0 ; i < numOfMembers ; i ++ ) 
	{
		this->parent[i] = -1 ;
		// ��� member�� ������ singleton set���� �ʱ�ȭ�Ѵ�.
		// �ʱ� ���¿���, �� member�� �ڽ��� ������ root�̸�, ũ��� 1 �̴�.
	}
}

PWDisjointSets::~PWDisjointSets ()
{
	// In reverse order of creation
	delete this->parent ;
}

SetID PWDisjointSets::find (SetMember member)
{
	int root, trail, lead;

	for(root=member; parent[root]>=0; root=parent[root]);//root�� ã�Ƶ���.

	for(trail=member; trail!=root; trail=lead)//trail�� root�� �����Ҷ�����
	{
		lead=parent[trail];//lead�� trail�� �θ�� �����Ѵ�.
		parent[trail]=root;//trail�� �θ� root�� �����Ѵ�. 
	}
	return root;//root��ȯ
	// Collapsing rule�� �����Ѵ�.
	// ���⸦ ä��ÿ�.
}

void PWDisjointSets::unionOfDisjointSets (SetID id1, SetID id2)
{
	if(find(id1)!=find(id2))
	{
		int temp=parent[id1]+parent[id2];//temp�� i�� j�� �θ��� ������ �Ѵ�.
		if(parent[id1]>parent[id2])//i�� ���� set�� ���Ҽ��� �� �������
		{
			parent[id1]=id2;//j�� i�� �θ� �ȴ�.
			parent[id2]=temp;//j�� �θ�� i�� j �θ��� ���̵ȴ�.
		}

		else//j�� ���Ҽ��� �� ���ų� �������
		{
			parent[id2]=id1;//i�� j�� �θ𰡵ȴ�
			parent[id1]=temp;//i�� �θ�� i�� j �θ��� ���̵ȴ�.
		}
	}

	
}