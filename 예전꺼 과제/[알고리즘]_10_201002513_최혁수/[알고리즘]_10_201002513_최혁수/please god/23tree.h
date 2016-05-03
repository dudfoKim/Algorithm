#ifndef _23tree_h
#define _23tree_h

typedef struct node23 {
        int small;  // 2-3Tree�� small��
        int large;
        struct node23* left;  // Left, Middle, Right Link
        struct node23* middle;
        struct node23* right;
        struct node23* parent;  // Split�� ���� �� ���� �θ����� �ּҸ� �����صд�.
} node23;

typedef struct tree23{  // 2-3Tree ����
        node23* root;  
} tree23;

node23* makeNode23();
tree23* makeTree23();
int isLeaf(node23* node);

/* Search ���� �Լ� */
node23* target23(node23* node, int key);
node23* search23(node23* node, int key);

/* Insert ���� �Լ� */
int* rearrange(int a, int b, int c);
void insertIntoNode23(tree23* tree, node23* node, int key);
void splitLeaf23(tree23* tree, node23* node, int key);
void splitNode23(tree23* tree, node23* node, node23* newChild, int key);
void insert23(tree23* tree, int key);

/* Delete ���� �Լ� */
node23* successor23(node23* node, int key);
void swapWithSuccessorRecursive(node23* node, int key);
int keyCount23(node23* node);
node23* deleteNode23(tree23* tree, node23* node, int key);
void delete23(tree23* tree, int key);
tree23* fixNode23(tree23* tree, node23* node);
void destroy23(node23* node);

/* Print ���� �Լ� */
void print23(tree23* tree);
void depthFirstPrint23(node23* node);
void printNode23(node23* node);

#endif