#ifndef __BINARY_HEADER2_H__
#define __BINARY_HEADER2_H__
#include <stdio.h>
#include <stdlib.h>

typedef struct bTreeNode{
	char data;  // Key값
	struct bTreeNode *left;  // Left, Right Link
	struct bTreeNode *right;
}BTreeNode; 

BTreeNode *MakeNode();  // 노드 메모리할당

char GetData(BTreeNode *bt);  // return data
void SetData(BTreeNode *bt, char data);  // store the data

/* return Left, Right SubTree */
BTreeNode *GetLeftSubTree(BTreeNode *bt);
BTreeNode *GetRightSubTree(BTreeNode *bt);

void InorderTraverse(BTreeNode *bt);

/* Free Memeory *bt->left, right = NULL */
BTreeNode *RemoveLeftSubTree(BTreeNode *bt);
BTreeNode *RemoveRightSubTree(BTreeNode *bt);

/* Change SubTree => root->left, right = sub */
void ChangeLeftSubTree(BTreeNode *root, BTreeNode *sub);
void ChangeRightSubTree(BTreeNode *root, BTreeNode *sub);

#endif