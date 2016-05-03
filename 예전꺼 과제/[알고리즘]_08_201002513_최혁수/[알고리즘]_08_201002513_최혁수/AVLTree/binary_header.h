#include "binary_header2.h"

void BSTInit(BTreeNode **Root);  // Init = NULL
char BSTGetNodeData(BTreeNode *bst);  // call GetData(bst);
BTreeNode *BSTInsert(BTreeNode **Root, char data);  // BSTree algorithm : Insert
BTreeNode *BSTSearch(BTreeNode *bst, char search);  // BSTree algorithm : Search

/* Delete 노드의 조건(단말, 자식노드 존재유무)에 따른 삭제구현 */
BTreeNode *BSTRemove(BTreeNode **Root, char search); 
/* Root 및 Left, Right child Node / InorderTraverse 결과 출력 */
void BSTShow(BTreeNode *bst);