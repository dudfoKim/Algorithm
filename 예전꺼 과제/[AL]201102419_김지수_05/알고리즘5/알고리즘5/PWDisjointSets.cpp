#include "PWDisjointSets.h"

PWDisjointSets::PWDisjointSets (int numOfMembers)
{
	this->size = numOfMembers ;
	this->parent = new SetMember [numOfMembers] ;
	for (int i = 0 ; i < numOfMembers ; i ++ ) 
	{
		this->parent[i] = -1 ;
		// 모든 member를 독립된 singleton set으로 초기화한다.
		// 초기 상태에서, 각 member가 자신의 집합의 root이며, 크기는 1 이다.
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

	for(root=member; parent[root]>=0; root=parent[root]);//root를 찾아들어간다.

	for(trail=member; trail!=root; trail=lead)//trail이 root에 도달할때까지
	{
		lead=parent[trail];//lead를 trail의 부모와 같게한다.
		parent[trail]=root;//trail의 부모를 root와 같게한다. 
	}
	return root;//root반환
	// Collapsing rule을 적용한다.
	// 여기를 채우시오.
}

void PWDisjointSets::unionOfDisjointSets (SetID id1, SetID id2)
{
	if(find(id1)!=find(id2))
	{
		int temp=parent[id1]+parent[id2];//temp를 i와 j의 부모값의 합으로 한다.
		if(parent[id1]>parent[id2])//i가 속한 set의 원소수가 더 적을경우
		{
			parent[id1]=id2;//j가 i의 부모가 된다.
			parent[id2]=temp;//j의 부모는 i와 j 부모값의 합이된다.
		}

		else//j의 원소수가 더 적거나 같을경우
		{
			parent[id2]=id1;//i가 j의 부모가된다
			parent[id1]=temp;//i의 부모는 i와 j 부모값의 합이된다.
		}
	}

	
}