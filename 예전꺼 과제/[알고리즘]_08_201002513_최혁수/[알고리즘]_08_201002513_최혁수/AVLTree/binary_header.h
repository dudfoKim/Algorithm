#include "binary_header2.h"

void BSTInit(BTreeNode **Root);  // Init = NULL
char BSTGetNodeData(BTreeNode *bst);  // call GetData(bst);
BTreeNode *BSTInsert(BTreeNode **Root, char data);  // BSTree algorithm : Insert
BTreeNode *BSTSearch(BTreeNode *bst, char search);  // BSTree algorithm : Search

/* Delete ����� ����(�ܸ�, �ڽĳ�� ��������)�� ���� �������� */
BTreeNode *BSTRemove(BTreeNode **Root, char search); 
/* Root �� Left, Right child Node / InorderTraverse ��� ��� */
void BSTShow(BTreeNode *bst);