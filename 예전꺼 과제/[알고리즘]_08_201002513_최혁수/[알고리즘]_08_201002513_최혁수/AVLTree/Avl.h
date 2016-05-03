#include "binary_header2.h"

/* �ұ��� ������ 4���� ����� �ٷ� ������� �Լ� */
/* check = LR, RL Rotate���� LL, RR�� ȣ���Ҷ� printf�� �����Ѵ�.*/
BTreeNode *LL_Rotate(BTreeNode *bst, int check);
BTreeNode *LR_Rotate(BTreeNode *bst, int check);
BTreeNode *RR_Rotate(BTreeNode *bst, int check);
BTreeNode *RL_Rotate(BTreeNode *bst, int check);

/* �ұ��� ����(�����μ�=Balance Factor)�� ���ϴ� �Լ� */
int GetHeight(BTreeNode * bst);
int GetHeightDiff(BTreeNode * bst);

/* BF�� ���缭 BSTree�� ������ Root���� ��ư���. */
BTreeNode *Rebalance(BTreeNode **Root);
