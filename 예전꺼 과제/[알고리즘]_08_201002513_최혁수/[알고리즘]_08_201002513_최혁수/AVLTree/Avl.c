#include "binary_header.h"
#include "binary_header2.h"

BTreeNode *LL_Rotate(BTreeNode *bst, int check){  // LL로 |BF|>1이 된 Tree를 Rotation하여 균형을 잡는다.
	BTreeNode *p_Node;  // parent node
	BTreeNode *c_Node;  // current node

	p_Node = bst; 
	c_Node = GetLeftSubTree(p_Node);  // parent의 왼쪽 자식

	ChangeLeftSubTree(p_Node, GetRightSubTree(c_Node));  // c_node의 오른쪽 자식주소를 p_node의 왼쪽자식으로 옮긴다.
	ChangeRightSubTree(c_Node, p_Node);  // c_node의 오른쪽 자식으로 p_node를 넣는다.
	if(check) printf("LL Rotation!!\n");
	return c_Node;  // rotation 하면서 c_node는 parent node가 되었다.
}

BTreeNode *RR_Rotate(BTreeNode *bst, int check){  // LL_Rotation 과 방향만 서로 다르게 전환
	BTreeNode *p_Node;
	BTreeNode *c_Node;

	p_Node = bst;
	c_Node = GetRightSubTree(p_Node);

	ChangeRightSubTree(p_Node, GetLeftSubTree(c_Node));
	ChangeLeftSubTree(c_Node, p_Node);
	if(check) printf("RR Rotation!!\n");
	return c_Node;
}

/* RL_Rotation == 1st : LL_Rotate -> 2nd : RR_Rotate */
BTreeNode *RL_Rotate(BTreeNode *bst, int check){
	BTreeNode *p_Node;
	BTreeNode *c_Node;

	p_Node = bst;
	c_Node = GetRightSubTree(p_Node);

	ChangeRightSubTree(p_Node, LL_Rotate(c_Node, 0));  // LL_Rotate
	if(check) printf("RL Rotation!!\n");
	return RR_Rotate(p_Node, 0);  // RR_Rotate
}

/* LR_Rotation == 1st : RR_Rotate -> 2nd : LL_Rotate */
BTreeNode *LR_Rotate(BTreeNode *bst, int check){
	BTreeNode *p_Node;
	BTreeNode *c_Node;
	BTreeNode *t_Node;

	p_Node = bst;
	c_Node = GetLeftSubTree(p_Node);

	ChangeLeftSubTree(p_Node, RR_Rotate(c_Node, 0));
	if(check) printf("LR Rotation!!\n");
	return LL_Rotate(p_Node, 0);
}

int GetHeight(BTreeNode *bst){ // Tree의 높이 계산

	int leftH;		// left height
	int rightH;   // right height

	if(bst == NULL) return 0;

	leftH = GetHeight(GetLeftSubTree(bst));  // 재귀적으로 왼쪽 서브트리 높이를 계산
	rightH = GetHeight(GetRightSubTree(bst));

	if(leftH > rightH) 
		return leftH + 1;  // 왼쪽, 오른쪽 높이를 비교하여 큰값 반환
	else
		return rightH + 1;
}

int GetHeightDiff(BTreeNode *bst){  // 왼쪽, 오른쪽 높이의 차를 반환

	int lsh;    // left sub tree height
	int rsh;    // right sub tree height

	if(bst == NULL) return 0;

	lsh = GetHeight(GetLeftSubTree(bst));
	rsh = GetHeight(GetRightSubTree(bst));

	return lsh - rsh;  // 균형인수(balance factor) 계산값 반환
}

BTreeNode *Rebalance(BTreeNode **pRoot)  // AVLTree를 완성시키는 단계(균형잡기)
{
	int hDiff = GetHeightDiff(*pRoot);  // 균형인수 저장
	if(hDiff > 1){  // 양수이면서 -1보다 크면, 왼쪽(L)으로 불균형 발생
		if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)  // 왼쪽자식의 균형인수가 0보다 크면,  LL
			*pRoot = LL_Rotate(*pRoot, 1);
		else
			// LR Rotate가 발생하는 시점은 부모의 균형인수가 1보다 크면서 자식노드는 0으로 균형이 잡힌 상태
			*pRoot = LR_Rotate(*pRoot, 1);  
	}
	
	if(hDiff < -1){  // 음수이면서 -1보다 작으면, 오른쪽(R)으로 불균형 발생
		if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0)
			*pRoot = RR_Rotate(*pRoot, 1);
		else
			*pRoot = RL_Rotate(*pRoot, 1);
	}
	return *pRoot;
}