#include "binary_header2.h"

/* 불규형 상태의 4가지 경우을 바로 잡기위한 함수 */
/* check = LR, RL Rotate에서 LL, RR을 호출할때 printf을 조율한다.*/
BTreeNode *LL_Rotate(BTreeNode *bst, int check);
BTreeNode *LR_Rotate(BTreeNode *bst, int check);
BTreeNode *RR_Rotate(BTreeNode *bst, int check);
BTreeNode *RL_Rotate(BTreeNode *bst, int check);

/* 불균형 조건(균형인수=Balance Factor)을 구하는 함수 */
int GetHeight(BTreeNode * bst);
int GetHeightDiff(BTreeNode * bst);

/* BF에 맞춰서 BSTree의 균형을 Root부터 잡아간다. */
BTreeNode *Rebalance(BTreeNode **Root);
