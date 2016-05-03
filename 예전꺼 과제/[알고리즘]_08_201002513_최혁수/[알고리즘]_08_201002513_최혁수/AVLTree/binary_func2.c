#include "binary_header2.h"

BTreeNode *MakeNode(void){
	BTreeNode *pt = (BTreeNode*)malloc(sizeof(BTreeNode));
	pt->left = pt->right = NULL;
	return pt;  // return = Init & malloc Node 
}

char GetData(BTreeNode *bt){ return bt->data; }
void SetData(BTreeNode *bt, char data){ bt->data = data; }

BTreeNode *GetLeftSubTree(BTreeNode *bt){ return bt->left; }
BTreeNode *GetRightSubTree(BTreeNode *bt){ return bt->right; }

void InorderTraverse(BTreeNode *bt){
	if(bt == NULL) return;  // empty? return:
	InorderTraverse(bt->left);
	printf("%c  ", bt->data);  // InorderTraverse
	InorderTraverse(bt->right);
}

BTreeNode *RemoveLeftSubTree(BTreeNode *bt){
	BTreeNode *d_Node;
	if(bt != NULL){
		d_Node = bt->left;
		bt->left = NULL;  // LeftSubTree를 NULL로 지정
	}
	return d_Node;
}

BTreeNode *RemoveRightSubTree(BTreeNode *bt){
	BTreeNode *d_Node;
	if(bt != NULL){
		d_Node = bt->right;
		bt->right = NULL;  // RightSubTree를 NULL로 지정
	}
	return d_Node;
}

void ChangeLeftSubTree(BTreeNode *root, BTreeNode *sub){
	root->left = sub;  // LeftSubTree를 sub으로 연결
}
void ChangeRightSubTree(BTreeNode *root, BTreeNode *sub){
	root->right = sub;  // RightSubTree를 sub으로 연결
}
