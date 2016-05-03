#include "binary_header.h"
#include "binary_header2.h"

BTreeNode *LL_Rotate(BTreeNode *bst, int check){  // LL�� |BF|>1�� �� Tree�� Rotation�Ͽ� ������ ��´�.
	BTreeNode *p_Node;  // parent node
	BTreeNode *c_Node;  // current node

	p_Node = bst; 
	c_Node = GetLeftSubTree(p_Node);  // parent�� ���� �ڽ�

	ChangeLeftSubTree(p_Node, GetRightSubTree(c_Node));  // c_node�� ������ �ڽ��ּҸ� p_node�� �����ڽ����� �ű��.
	ChangeRightSubTree(c_Node, p_Node);  // c_node�� ������ �ڽ����� p_node�� �ִ´�.
	if(check) printf("LL Rotation!!\n");
	return c_Node;  // rotation �ϸ鼭 c_node�� parent node�� �Ǿ���.
}

BTreeNode *RR_Rotate(BTreeNode *bst, int check){  // LL_Rotation �� ���⸸ ���� �ٸ��� ��ȯ
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

int GetHeight(BTreeNode *bst){ // Tree�� ���� ���

	int leftH;		// left height
	int rightH;   // right height

	if(bst == NULL) return 0;

	leftH = GetHeight(GetLeftSubTree(bst));  // ��������� ���� ����Ʈ�� ���̸� ���
	rightH = GetHeight(GetRightSubTree(bst));

	if(leftH > rightH) 
		return leftH + 1;  // ����, ������ ���̸� ���Ͽ� ū�� ��ȯ
	else
		return rightH + 1;
}

int GetHeightDiff(BTreeNode *bst){  // ����, ������ ������ ���� ��ȯ

	int lsh;    // left sub tree height
	int rsh;    // right sub tree height

	if(bst == NULL) return 0;

	lsh = GetHeight(GetLeftSubTree(bst));
	rsh = GetHeight(GetRightSubTree(bst));

	return lsh - rsh;  // �����μ�(balance factor) ��갪 ��ȯ
}

BTreeNode *Rebalance(BTreeNode **pRoot)  // AVLTree�� �ϼ���Ű�� �ܰ�(�������)
{
	int hDiff = GetHeightDiff(*pRoot);  // �����μ� ����
	if(hDiff > 1){  // ����̸鼭 -1���� ũ��, ����(L)���� �ұ��� �߻�
		if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)  // �����ڽ��� �����μ��� 0���� ũ��,  LL
			*pRoot = LL_Rotate(*pRoot, 1);
		else
			// LR Rotate�� �߻��ϴ� ������ �θ��� �����μ��� 1���� ũ�鼭 �ڽĳ��� 0���� ������ ���� ����
			*pRoot = LR_Rotate(*pRoot, 1);  
	}
	
	if(hDiff < -1){  // �����̸鼭 -1���� ������, ������(R)���� �ұ��� �߻�
		if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0)
			*pRoot = RR_Rotate(*pRoot, 1);
		else
			*pRoot = RL_Rotate(*pRoot, 1);
	}
	return *pRoot;
}