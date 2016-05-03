#include "Avl.h"
#include "binary_header.h"
#include "binary_header2.h"

void BSTInit(BTreeNode **Root){ *Root = NULL; }  // Init = NULL

char BSTGetNodeData(BTreeNode *bst){ return GetData(bst); }  // call GetData();

BTreeNode *BSTInsert(BTreeNode **Root, char data){
	if(*Root == NULL){  // BSTree is Empty? || ���ȣ��� Data�� �ڸ� Ž�� �Ϸ��
		*Root = MakeNode();  // Init & malloc
		SetData(*Root, data);  // *Root->data = data;
	}
	else if(data < GetData(*Root)){  // ���� ����Ʈ���� ���� ���(������ < �θ���.������)
		BSTInsert(&((*Root)->left), data);  // ���ȣ��� Data�� �ڸ� Ž�� �� ����
		*Root = Rebalance(Root);  // ���� �� Root���� Rebalance(); ����
	}
	
	else if(data > GetData(*Root)){  // ������ ����Ʈ���� ���� ���
		BSTInsert(&((*Root)->right), data);
		*Root = Rebalance(Root);
	}
	else
		return NULL;  // Ž�� ����

	return *Root;  // ���� ��  *Root ��ȯ
}

BTreeNode *BSTSearch(BTreeNode *bst, char search){
	BTreeNode *c_Node = bst;  // current node = bst
	char c_data;  // current node�� data

	while(c_Node != NULL){  // Ž�����б��� ��, ���ܳ����� Ž��
		c_data = GetData(c_Node);  // �����͸� ��´�.

		if(search == c_data) return c_Node;  // Ž�� �Ϸ� �� return current node
		else if(search < c_data)  // ���� ����Ʈ���� �ִ� ���
			c_Node = GetLeftSubTree(c_Node);  // ���ʼ���Ʈ���� Root�� ��ȯ�Ͽ� c_Node�� ����
		else
			c_Node = GetRightSubTree(c_Node);
	}
	return NULL;  // Ž�� ����
}

/* Delete ����� ����(�ܸ�, �ڽĳ�� ��������)�� ���� �������� */
BTreeNode *BSTRemove(BTreeNode **Root, char search){
	BTreeNode *temp = MakeNode();  // �ӽó�� Init & malloc
	BTreeNode *p_Node = temp;  // parent node�� temp�� ����Ų��.
	BTreeNode *c_Node = *Root;  // current node�� root�� ����Ų��.
	BTreeNode *d_Node;  // delete node

	while(c_Node!=NULL && GetData(c_Node)!=search){  // search�� key�� ���� node Ž��
		p_Node = c_Node;  // Ž�� �� p_Node�� c_Node�� parent.
		if(search < GetData(c_Node))  // search�� ���� ����Ʈ���� �ִ� ���
			c_Node = GetLeftSubTree(c_Node);  // ���� ����Ʈ���� root�� ������ current node�� ����
		else
			c_Node = GetRightSubTree(c_Node);
	}
	if(c_Node == NULL) return NULL;  // Ž�� ����

	d_Node = c_Node;  // delete node�� current node�� ����Ų��.

	/* delete node�� ���ܳ���� ��� */
	if(GetLeftSubTree(d_Node)==NULL && GetRightSubTree(d_Node)==NULL){
		if(GetLeftSubTree(p_Node) == d_Node)  // parent�� �������� delete node�� ã�´�.
			RemoveLeftSubTree(p_Node);  // ���� �ڽ��� ��� Node ���� : p_Node->left = NULL;
		else
			RemoveRightSubTree(p_Node);
	}
	/* delete node�� �ڽĳ�带 1�� ������ �ִ� ��� */
	else if(GetLeftSubTree(d_Node)==NULL || GetRightSubTree(d_Node)==NULL){
		BTreeNode *d_c_Node;  // d_c_Node : delete child Node(��������� �ڽĳ��)
		if(GetLeftSubTree(d_Node) != NULL)  // �����ڽ��� ����
			d_c_Node = GetLeftSubTree(d_Node);  // d_c_Node�� ����Ų��.
		else
			d_c_Node = GetRightSubTree(d_Node);

		if(GetLeftSubTree(p_Node) == d_Node)  // delete node�� parent node�� ���� �ڽ��� ���
			ChangeLeftSubTree(p_Node, d_c_Node);  // parent node�� ���� �ڽ��� d_c_Node�� ��ü
		else
			ChangeRightSubTree(p_Node, d_c_Node);
	}

	/* delete node�� �ڽĳ�带 2�� ��� ���� ��� */ 
	else{
		BTreeNode *m_Node = GetRightSubTree(d_Node);
		BTreeNode *m_p_Node = d_Node;
		int delete_data;

		/* delete node�� �������ڽ��� ���� �ڽ��� ���� Ȯ�� */
		/* ��, delete node�� ��ü�� ��带 Ž���ϴ� ���� */
		while(GetLeftSubTree(m_Node) != NULL){ 
			m_p_Node = m_Node; 
			m_Node = GetLeftSubTree(m_Node);
		}

		delete_data = GetData(d_Node);  // Set delete_data
		SetData(d_Node, GetData(m_Node));  // d_Node�� data�� ������ �ڽ��� �����ͷ� ��ü.

		if(GetLeftSubTree(m_p_Node) == m_Node)  // d_Node�� ��ü data�� ���� node�� �θ��� ���� �ڽ��� ���
			/* ������ m_Node�� LeftSubTree�� Null�϶����� Ȯ���Ͽ����Ƿ� */
			/* RightSubTree�� �ּҰ��� ���ͼ� m_p_Node�� leftSubTree�� ��ü�Ѵ�. */
			ChangeLeftSubTree(m_p_Node, GetRightSubTree(m_Node));  
		else
			ChangeRightSubTree(m_p_Node, GetRightSubTree(m_Node));

		/* delete node�� ��ü�� ��带 ���� �ٲ۴�. */
		d_Node = m_Node;  // d_node�� m_node�� ����Ų��.
		SetData(d_Node, delete_data);  // ������ ���ߴ� data���� Set�Ѵ�.
	}
	free(temp);  // �ӽ÷� �Ҵ��� node�� �޸𸮸� ����
	*Root=Rebalance(Root);  // Root�� �������� balance()�� ��ȯ�� *Root�� �ѱ��.
	return d_Node; 
}

void BSTShow(BTreeNode *bst){
	printf("Root : %c\n", bst->data);
	if(bst->left!=NULL)  // ���� �ڽ� ����
	printf("Root->left_child : %c   ", GetData(bst->left));
	if(bst->right!=NULL)  // ������ �ڽ� ����
	printf("Root->Right_child : %c\n", GetData(bst->right));
	printf("Traversal : ");  // InorderTraverse
	InorderTraverse(bst);
}