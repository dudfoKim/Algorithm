#include "Avl.h"
#include "binary_header.h"
#include "binary_header2.h"

void BSTInit(BTreeNode **Root){ *Root = NULL; }  // Init = NULL

char BSTGetNodeData(BTreeNode *bst){ return GetData(bst); }  // call GetData();

BTreeNode *BSTInsert(BTreeNode **Root, char data){
	if(*Root == NULL){  // BSTree is Empty? || 재귀호출로 Data의 자리 탐색 완료시
		*Root = MakeNode();  // Init & malloc
		SetData(*Root, data);  // *Root->data = data;
	}
	else if(data < GetData(*Root)){  // 왼쪽 서브트리에 있을 경우(데이터 < 부모노드.데이터)
		BSTInsert(&((*Root)->left), data);  // 재귀호출로 Data의 자리 탐색 후 삽입
		*Root = Rebalance(Root);  // 삽입 후 Root부터 Rebalance(); 진행
	}
	
	else if(data > GetData(*Root)){  // 오른쪽 서브트리에 있을 경우
		BSTInsert(&((*Root)->right), data);
		*Root = Rebalance(Root);
	}
	else
		return NULL;  // 탐색 실패

	return *Root;  // 삽입 후  *Root 반환
}

BTreeNode *BSTSearch(BTreeNode *bst, char search){
	BTreeNode *c_Node = bst;  // current node = bst
	char c_data;  // current node의 data

	while(c_Node != NULL){  // 탐색실패까지 즉, 말단노드까지 탐색
		c_data = GetData(c_Node);  // 데이터를 얻는다.

		if(search == c_data) return c_Node;  // 탐색 완료 시 return current node
		else if(search < c_data)  // 왼쪽 서브트리에 있는 경우
			c_Node = GetLeftSubTree(c_Node);  // 왼쪽서브트리의 Root를 반환하여 c_Node에 적용
		else
			c_Node = GetRightSubTree(c_Node);
	}
	return NULL;  // 탐색 실패
}

/* Delete 노드의 조건(단말, 자식노드 존재유무)에 따른 삭제구현 */
BTreeNode *BSTRemove(BTreeNode **Root, char search){
	BTreeNode *temp = MakeNode();  // 임시노드 Init & malloc
	BTreeNode *p_Node = temp;  // parent node는 temp를 가리킨다.
	BTreeNode *c_Node = *Root;  // current node는 root를 가리킨다.
	BTreeNode *d_Node;  // delete node

	while(c_Node!=NULL && GetData(c_Node)!=search){  // search를 key로 갖는 node 탐색
		p_Node = c_Node;  // 탐색 후 p_Node는 c_Node의 parent.
		if(search < GetData(c_Node))  // search가 왼쪽 서브트리에 있는 경우
			c_Node = GetLeftSubTree(c_Node);  // 왼쪽 서브트리의 root를 가져와 current node로 지정
		else
			c_Node = GetRightSubTree(c_Node);
	}
	if(c_Node == NULL) return NULL;  // 탐색 실패

	d_Node = c_Node;  // delete node는 current node를 가리킨다.

	/* delete node가 말단노드일 경우 */
	if(GetLeftSubTree(d_Node)==NULL && GetRightSubTree(d_Node)==NULL){
		if(GetLeftSubTree(p_Node) == d_Node)  // parent를 기준으로 delete node를 찾는다.
			RemoveLeftSubTree(p_Node);  // 왼쪽 자식의 경우 Node 삭제 : p_Node->left = NULL;
		else
			RemoveRightSubTree(p_Node);
	}
	/* delete node가 자식노드를 1개 가지고 있는 경우 */
	else if(GetLeftSubTree(d_Node)==NULL || GetRightSubTree(d_Node)==NULL){
		BTreeNode *d_c_Node;  // d_c_Node : delete child Node(삭제노드의 자식노드)
		if(GetLeftSubTree(d_Node) != NULL)  // 왼쪽자식이 존재
			d_c_Node = GetLeftSubTree(d_Node);  // d_c_Node가 가리킨다.
		else
			d_c_Node = GetRightSubTree(d_Node);

		if(GetLeftSubTree(p_Node) == d_Node)  // delete node가 parent node의 왼쪽 자식일 경우
			ChangeLeftSubTree(p_Node, d_c_Node);  // parent node의 왼쪽 자식을 d_c_Node로 대체
		else
			ChangeRightSubTree(p_Node, d_c_Node);
	}

	/* delete node가 자식노드를 2개 모두 가진 경우 */ 
	else{
		BTreeNode *m_Node = GetRightSubTree(d_Node);
		BTreeNode *m_p_Node = d_Node;
		int delete_data;

		/* delete node의 오른쪽자식의 왼쪽 자식의 존재 확인 */
		/* 즉, delete node를 대체할 노드를 탐색하는 과정 */
		while(GetLeftSubTree(m_Node) != NULL){ 
			m_p_Node = m_Node; 
			m_Node = GetLeftSubTree(m_Node);
		}

		delete_data = GetData(d_Node);  // Set delete_data
		SetData(d_Node, GetData(m_Node));  // d_Node의 data를 오른쪽 자식의 데이터로 대체.

		if(GetLeftSubTree(m_p_Node) == m_Node)  // d_Node의 대체 data을 가진 node가 부모의 왼쪽 자식일 경우
			/* 위에서 m_Node의 LeftSubTree는 Null일때까지 확인하였으므로 */
			/* RightSubTree의 주소값을 빼와서 m_p_Node의 leftSubTree로 대체한다. */
			ChangeLeftSubTree(m_p_Node, GetRightSubTree(m_Node));  
		else
			ChangeRightSubTree(m_p_Node, GetRightSubTree(m_Node));

		/* delete node와 대체된 노드를 서로 바꾼다. */
		d_Node = m_Node;  // d_node는 m_node를 가리킨다.
		SetData(d_Node, delete_data);  // 삭제를 원했던 data값을 Set한다.
	}
	free(temp);  // 임시로 할당한 node의 메모리를 해제
	*Root=Rebalance(Root);  // Root를 기준으로 balance()의 반환을 *Root로 넘긴다.
	return d_Node; 
}

void BSTShow(BTreeNode *bst){
	printf("Root : %c\n", bst->data);
	if(bst->left!=NULL)  // 왼쪽 자식 존재
	printf("Root->left_child : %c   ", GetData(bst->left));
	if(bst->right!=NULL)  // 오른쪽 자식 존재
	printf("Root->Right_child : %c\n", GetData(bst->right));
	printf("Traversal : ");  // InorderTraverse
	InorderTraverse(bst);
}