#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "23tree.h"

tree23* makeTree23(){  // Init_Alloc Tree  & return Tree
        tree23* newTree = (tree23*)malloc(sizeof(tree23));
        newTree->root = NULL;
        return newTree;
}

node23* makeNode23(){  // Init_Alloc Node & return Node
        node23* newNode = (node23*)malloc(sizeof(node23));
        newNode->small = newNode->large = 0;
        newNode->left = newNode->middle = newNode->right = newNode->parent = NULL;
        return newNode;
}

int isLeaf(node23* node){  // Node�� Leaf���� Check
        if (!node->left && !node->middle && !node->right) {
                return 1;  // Left = return 1
        } else {
                return 0;
        }
}

node23* target23(node23* node, int key){  // Key�� ���� Target Node�� ã�´�
        node23* newNode = NULL;
        if (isLeaf(node)) return node;  // Leaf node�̸� �ش��带 ����
        if (key == node->small || key == node->large) return NULL;  // Key�� �����ϸ� NULL ��ȯ
        if (keyCount23(node) == 1){  // node�� data�� 1���̸�(=Only exist small data)
				// ���� �ڽ��� �����ϰ�,  small������ key�� ������ = �����ڽĿ��� target �����
                if (key < node->small && node->left) newNode = target23(node->left, key);
				// �߰� �ڽ��� �����ϰ�, small������ Ŭ��
                if (key > node->small && node->middle) newNode = target23(node->middle, key);
        }
		else{  // node�� �����Ͱ� 2��(=��, small, large�� �Ѵ� ����)
                if (key < node->small && node->left) newNode = target23(node->left, key);
                if (key > node->small && key < node->large && node->middle) newNode = target23(node->middle, key);
				// ������ �ڽ��� �����ϰ�, large������ Ŭ��
                if (key > node->large && node->right) newNode = target23(node->right, key);
        }
        return newNode;  // targer node�� ��ȯ
}

node23* search23(node23* node, int key){  // target23()�Լ��� ������ ��������� ��ȯ�� & if���� ���Ǵ� �ٸ���.
        node23* newNode = NULL;
		// key�� ã���� �ش� node�� ��ȯ�Ѵ�.
        if(key == node->small || key == node->large) return node;
        else if(isLeaf(node)) return NULL;  // leaf���� key�� �������� �����Ƿ� NULL ��ȯ
        if(!node->large){  // node->large���� �����ϸ�  
                if (key < node->small && node->left) newNode = search23(node->left, key);
                if (key > node->small && node->middle) newNode = search23(node->middle, key);
        }
		else{ // node->large���� �������� ������
                if (key < node->small && node->left) newNode = search23(node->left, key);
                if (key > node->small && key < node->large && node->middle) newNode = search23(node->middle, key);
                if (key > node->large && node->right) newNode = search23(node->right, key);
        }
        return newNode;  // target node�� ��ȯ
}


int* rearrange(int a, int b, int c){  // 2���� data�� ���� 2-3node�� 'Insert' ���� ������ ũ������� ����
        int* newTemp = (int*)malloc(sizeof(int)*3);
		int i, j;
        newTemp[0] = a; newTemp[1] = b; newTemp[2] = c;  // �ӽ�����
        
        for (j=0; j<3; j++)
        for (i=0; i<2; i++){
        int temp;
        if (newTemp[i] > newTemp[i+1]){  // ������ ���� ������ ũ��� ���������� �̷��.
                        temp = newTemp[i];
                        newTemp[i] = newTemp[i+1];
                        newTemp[i+1] = temp;
                }
        }
        return newTemp;  // newTemp�� �ּҹ�ȯ
}

  // �������� Insert ���� �Լ��̸�, �������� ������ ���� Split�� �߻�����
  // 2-3Tree �˰��� ���� ��ġ��Ų��.
void insertIntoNode23(tree23* tree, node23* node, int key){
		int* newNode;
        if(isLeaf(node)){  // Leaf node���
                if (!keyCount23(node)){  // node�� �����Ͱ� �������� ������
                        node->small = key;  // small���� ����
                }
				else if(keyCount23(node) == 1) {  // �����Ͱ� 1�� ����(=int small)
                        node->large = key;  // large�� ����
                }
				else{  // 2���� �����Ͱ� �����ϴ� ��忡 Key�� �߰��� ������(3�� ������ = Split)
                        newNode = rearrange(node->small, node->large, key);  // ���ĵ� �����͸� newNode�� ����Ų��.
                        node->small = newNode[0]; node->large = newNode[2];  // �߰����� ������ �� �����͸� ���� ����
                        splitLeaf23(tree, node, newNode[1]);  // promoted�� node & data�� ������ Split�� �߻�
                }
                return;
        }
		else{  // Leaf node�� �ƴѰ�� key������ node�� targeting �Ѵ�.
                node23* tempLeaf = target23(node, key);
				// target23() ȣ���� �ӽ÷� ����� tempLeaf�� ����Ű�� ��� & key�� ���Ž�� ����
                if(tempLeaf) insertIntoNode23(tree, tempLeaf, key); 
                return;
        }
}

void splitLeaf23(tree23* tree, node23* node, int key)  // Leaf node���� Split�� �߻��Ҷ� ȣ��Ǵ� �Լ�
{
		int newKey=0;  // Key�� �ӽ�����
        if (isLeaf(node)){  // Leaf node�϶�
                if(!node->parent){  // node�� parent�� ���� ���°��(=Tree�� Node�� 1�� �����Ҷ� split�� �Ͼ ���)
                        node23* newChild = makeNode23();  // ���ο� �ڽĳ�� ����
                        node23* newRoot = makeNode23();  // ���ο� ��Ʈ��� ����
						// �⺻ �˰����� Split�� �Ͼ ����� large���� ���ο� �ڽĳ���� small������ �ű��
						// ���ο� ��Ʈ����� key���� split��(3���� �������� �߰���)�� ������, ���� �ڽ��� �������, �߰����� �� �ڽĳ��� ����
						// ������ Root�� newRoot�� node�� ��ü�Ѵ�.
                        newChild->small = node->large; node->large = 0; newChild->parent = node->parent = newRoot;
                        newRoot->small = key; newRoot->left = node; newRoot->middle = newChild;
                        tree->root = newRoot;  // Tree->root�� newRoot�� ����Ų��.(Root�� ��ü)
                        return;
                }
                if(node->parent){  // parent�� ����(=�ټ��� Node�� ���� Tree���� parent�� ������ leaf ��尡 Split�� ���)
                        node23* newChild = makeNode23();  // ���ο� �ڽĳ�� ����
                        newChild->small = node->large; node->large = 0;  // Leaf node�� large���� ���ο� �ڽ��� small������ �ְ� �ʱ�ȭ(0)
                        if(keyCount23(node->parent) == 1){  // Node�� parent�� ������ ������ 1�� �϶�(=small, 1-2Node)
                                if (key < node->parent->small){  // �θ��� small������ key�� �������
									  // key�� �����ϱ� ���� �� ������ �� �ڽĿ����� ���������� �Ѵܰ� �̵�
                                        node->parent->right = node->parent->middle;
                                        node->parent->large = node->parent->small;
									  // �߰��ڽ��� ���ο� �ڽĳ��� ����
                                        node->parent->middle = newChild;
									  // newChild�� parent�� node�� parent�� �����Ƿ� ����
                                        newChild->parent = node->parent;
									  // key�� ����
                                        node->parent->small = key;
                                        return;
                                }
                                if(key > node->parent->small){  // key�� small������ Ŭ��(���� large���� ����)
                                        node->parent->right = newChild;
                                        newChild->parent = node->parent;
                                        node->parent->large = key;
                                        return;
                                }
                        }
                        if(keyCount23(node->parent) == 2){  // parent node�� �����Ͱ� 2�� ������ ��� (2-3 Node)
							    /** �⺻ �˰����� ���� �����ϳ� ������(Large)�� ���� �����ϹǷ� ���ǹ��� 1�� �� �߰��Ǿ� �����ȴ�. **/
                                node23* newNode = makeNode23();
                                if (key < node->parent->small) {
                                        newNode->left = node->parent->middle;newNode->middle = node->parent->right;
                                        newNode->small = node->parent->large;
                                        node->parent->middle = node->parent->right = NULL;
                                        node->parent->large = 0;
                                        node->parent->middle = newChild; 
                                        newChild->parent = node->parent;
                                        newKey = node->parent->small;
                                        node->parent->small = key;
                                        splitNode23(tree, node->parent, newNode, newKey);
                                        return;
                                }
                                if (key > node->parent->small && key < node->parent->large) {
                                        newNode->left = newChild; newChild->parent = newNode; newNode->middle = node->parent->right;
                                        newNode->small = node->parent->large;
                                        node->parent->right = NULL;                                        
                                        node->parent->large = 0;
                                        splitNode23(tree, node->parent, newNode, key);
                                        return;
                                }
                                if (key > node->parent->large) {
                                        newNode->left = node->parent->right; newNode->middle = newChild;
                                        newChild->parent = newNode;
                                        newNode->small = key; node->parent->right = NULL;
                                        newKey = node->parent->large; node->parent->large  = 0;
                                        splitNode23(tree, node->parent, newNode, newKey);
                                        return;
                                }                                        
                        }
                }
        }                
}
  /* Leaf node�� �ƴ� Tree�� �߰���忡�� Split�� �Ͼ ���                                                              
     �����ʹ� Leaf node�� �������� insert �ǹǷ�, �ش� Split�� insert�� ���� splitLeaf23()�κ��� �߻��Ǿ���. */
void splitNode23(tree23* tree, node23* node, node23* newChild, int key)
{
	    int newKey=0;
        if (!node->parent) {  // parent node�� ���� Tree���� ���� ����� ���(�� splitLeaf23()�� �� ���ǰ� ����)
                node23* newRoot = makeNode23();
                newRoot->small = key;
                newRoot->left = node; newRoot->middle = newChild;
                node->parent = newChild->parent = newRoot;
                tree->root = newRoot;
                return;
        }
        if (keyCount23(node->parent) == 1) {  // parent�� �����Ͱ� 1���� ���(=1-2 Node), (�� splitLeaf23() �� ����)
                if (key < node->parent->small) {  // small������ ������
                        node->parent->right = node->parent->middle;
                        node->parent->large = node->parent->small;
                        node->parent->middle = newChild;
                        newChild->parent = node->parent;
                        node->parent->small = key;
                        return;
                }
                if (key > node->parent->small) {  // small������ Ŭ��
                        node->parent->right = newChild;
                        newChild->parent = node->parent;
                        node->parent->large = key;
                        return;
                }
        }
        if (keyCount23(node->parent) == 2) {  // parent�� �����Ͱ� 2�� �����ϴ� ���(=2-3Node)
                node23* newNode = makeNode23();
                if (key < node->parent->small) {
					// �⺻�˰����� splitLeaf23�� �����ϰ� key���� �����ϱ� ���� data�� child link�� �ش� ��ġ�� �Ѵܰ� �̵��ϸ�,
					// parent�� ������ Ȥ�� key���� newKey�� ������ �� �ٽ� Split�� �߻��� parent node���� Promoted�� �� ������ �ݺ��� Split�� �߻���Ų��.
                        newNode->left = node->parent->middle; newNode->small = node->parent->large; newNode->middle = node->parent->right;
                        node->parent->middle = newChild; newChild->parent = node->parent; node->parent->large = 0; node->parent->right = NULL;
                        newKey = node->parent->small; node->parent->small = key;
                        splitNode23(tree, node->parent, newNode, newKey);
                        return;
                }
                if (key > node->parent->small && key < node->parent->large) {  // small < key < large ���
                        newNode->left = newChild; newChild->parent = newNode; newNode->small = node->parent->large; newNode->middle = node->parent->right;
                        node->parent->large = 0; node->parent->right = NULL;
                        // promoted key = key(�߰���)
						newKey = key; 
                        splitNode23(tree, node->parent, newNode, newKey);
                        return;
                }
                if (key > node->parent->large) {  // small < large < key ���
                        newNode->left = node->parent->right; newNode->small = key; newNode->middle = newChild;
                        newChild->parent = newNode;
                        node->parent->right = NULL;
						// promoted key = parent->large(�߰���)
                        newKey = node->parent->large; node->parent->large = 0;
                        splitNode23(tree, node->parent, newNode, newKey);
                        return;
                }
        }
}
                                                                
void insert23(tree23* tree, int key){  // Key���� Insert�Ҷ� ó�� ȣ��Ǵ� �Լ�

	    node23* newNode;
        if (tree->root) insertIntoNode23(tree, tree->root, key);  // Leaf Node�� �ƴѰ�� Ž�� & ���� ������ �����
        if (!tree->root) {  // Leaf Node�� ���
                newNode = makeNode23();
                tree->root = newNode;  // Leaf node�� ���, Root�� �Ҵ��� ���ο� ��带 ����Ű�� �����.
												// �̴� Tree���� Node�� Empty�����϶� �Ͼ�� Insert Key�� Tree�� �����ϴ�
												// insert23()�� ȣ��ȴ�.
                insert23(tree, key);
                return;
        }
}

// ������ Key�� Rucursion�������� �κ��Լ��� ���� successor Key�� ��ü�� �� ������ ����
node23* successor(node23* node, int key){  

        if (key != node->small && key != node->large){  // node�� Key���� ������ NULL ����
                return NULL;
        }
        if (key == node->small) {  // small���� key���� ������� �߰��ڽ��� ����
                return node->middle;
        }
        if (key == node->large) {
                return node->right;
        }
		return 0;
}

// ���� successor�Լ��� ��Ƽ��� Recursive�� �����Ͽ� ��ü�� Key�� ã�´�.
void swapWithSuccessorRecursive(node23* node, int key){  

        if (successor(node, key)) {
                node23* temp = successor(node, key);
                if (key == node->small) {
                        node->small = temp->small;
                        temp->small = key;
                }
                if (key == node->large) {
                        node->large = temp->small;
                        temp->small = key;
                }
                swapWithSuccessorRecursive(temp, key);
        }
}

int keyCount23(node23* node){  // node�� ��ȿ �����ͼ��� ����

		int n = 0;
        if (!node) return 0;
        if (node->small) n++;
        if (node->large) n++;
        return n;
}                                        

node23* deleteNode23(tree23* tree, node23* node, int key){  // key���� ã�� �� delete ����

        if (!isLeaf(node)){
                node23* match = search23(node, key);  // key���� ���� node�� math�� ����Ų��.
                if (match) {  // key���� �����ϸ� ����� �ڽĳ�带 Recursive�ϰ� Ž���Ͽ� �ش� node�� �����Ͱ��� �����Ѵ�.
                        swapWithSuccessorRecursive(match, key);
                        deleteNode23(tree, match, key);  // �ܸ������� �� �� �Լ��� ���ȣ��
                        return node;  // node�� key
                } else {
                        return NULL;  // ������ key�� �������� ������ NULL ����
                }
        } 
		else {  // �ܸ������ ��� key���� �����ϰ� ������ ��ġ�� �ٸ� �����ͷ� ��ü�Ѵ�.
                if (key == node->large) {
                        node->large = 0;
                        return node;
                }
                if (key == node->small && node->large) {
                        node->small = node->large;
                        node->large = 0;
                        return node;
                }
                if (key == node->small && !node->large){ 
                        if (!node->parent){ // parent�� NULL�϶�, key�� �����ϸ� Tree�� empty�� �Ǹ� null�� ��ȯ
                                tree->root = NULL;
                                return NULL;
                        }
						// parent�� ������ ��� �˰����� key���� �����ϸ� ������ node�� ��� �����鼭 parent�� parent�� child�� ������ ������ 
						// �����Ͽ� node�� �����ϸ鼭 key, child link�� �̵���Ų��.
                        if (keyCount23(node->parent) == 1) {  // �����͸� 1�� ������ �ִ� ��� : redistribute ����
                                if (key < node->parent->small) {  // key < small�϶�
										// �θ��� small���� node�� ������ �� �θ��߰��ڽ��� small�����ͷ� ��ü
                                        node->small = node->parent->small;
                                        node->parent->small = node->parent->middle->small;
										// �θ��� �߰��ڽ��� ��ȿ�����Ͱ� 2�� ������ ���
                                        if (keyCount23(node->parent->middle) == 2){
												// �θ��� small�� ������ �߰��ڽ��� small�� �ڸ��� large�� �����ͷ� ��ü�� �� large �ʱ�ȭ(0)
                                                node->parent->middle->small = node->parent->middle->large;
                                                node->parent->middle->large = 0;
												// �����̵Ǿ����Ƿ� �ش� ��� return
                                                return node;
                                        }
										// �߰��ڽ��� �����Ͱ� 1���� ���, �� �����͸� node�� ������ �� �߰��ڽ��� ���� �� parent���� fixing �Ѵ�.
                                        node->parent->small = 0;
                                        node->large = node->parent->middle->small;
                                        destroy23(node->parent->middle);
                                        fixNode23(tree, node->parent);
                                        return node;
                                } else {
                                        node->small = node->parent->small;
                                        node->parent->small = 0;
                                        if (keyCount23(node->parent->left) == 2) {
                                                node->parent->small = node->parent->left->large;
                                                node->parent->left->large = 0;
                                                return node;
                                        }
                                        node->parent->left->large = node->small;
                                        destroy23(node->parent->middle);
                                        fixNode23(tree, node->parent);
                                        return node;
                                }
                        } else if (keyCount23(node->parent) == 2) {  // �θ��� �����Ͱ� 2���� ��� : merge�� ����
                                if (key < node->parent->small) {
                                        if (keyCount23(node->parent->middle) == 2) {
                                                node->small = node->parent->small;
                                                node->parent->small = node->parent->middle->small;
                                                node->parent->middle->small = node->parent->middle->large;
                                                node->parent->middle->large = 0;
                                                return node;
                                        } else if (keyCount23(node->parent->right) == 2) {
                                                node->small = node->parent->small;
                                                node->parent->small = node->parent->middle->small;                
                                                node->parent->middle->small = node->parent->large;
                                                node->parent->large = node->parent->right->small;
                                                node->parent->right->small = node->parent->right->large;
                                                node->parent->right->large = 0;
                                                return node;
                                        } else {
                                                node->small = node->parent->small;
                                                node->large = node->parent->middle->small;
                                                node->parent->small = node->parent->large;
                                                node->parent->middle->small = node->parent->right->small;
                                                node->parent->large = 0;
                                                destroy23(node->parent->right);
                                                return node;
                                        }
                                } else if (key < node->parent->small && key > node->parent->large) {
                                        if (keyCount23(node->parent->left) == 2) {
                                                node->small = node->parent->small;
                                                node->parent->small = node->parent->left->large;
                                                node->parent->left->large = 0;
                                                return node;
                                        } else if (keyCount23(node->parent->right) == 2) {
                                                node->small = node->parent->large;
                                                node->parent->large = node->parent->right->small;
                                                node->parent->right->small = node->parent->right->large;
                                                node->parent->right->large = 0;
                                                return node;
                                        } else {
                                                node->small = node->parent->large;
                                                node->large = node->parent->right->small;
                                                node->parent->large = 0;
                                                destroy23(node->parent->right);
                                                return node;
                                        }
                                } else {
                                        if (keyCount23(node->parent->middle)==2) {
                                                node->small = node->parent->large;
                                                node->parent->large = node->parent->middle->large;
                                                node->parent->middle->large = 0;
                                                return node;
                                        } else if (keyCount23(node->parent->left) == 2) {
                                                node->small = node->parent->large;
                                                node->parent->large = node->parent->middle->small;
                                                node->parent->middle->small = node->parent->small;
                                                node->parent->small = node->parent->left->large;
                                                node->parent->left->large = 0;
                                                return node;
                                        } else {
                                                node->parent->middle->large = node->parent->large;
                                                destroy23(node->parent->middle);
                                                return node;
                                        }
                                }
                        }
                }
        }
        return NULL;
}

void delete23(tree23* tree, int key)  // Ʈ���� Ʈ������ node�� �����Ҷ� ����
{
        if (tree && tree->root) deleteNode23(tree, tree->root, key);
}

/*  */
tree23* fixNode23(tree23* tree, node23* node)
{
        if (!node->parent) {
                tree->root = node->left;
                tree->root->parent = NULL; 
                destroy23(node);
                return tree;
        }
        if (keyCount23(node->parent) == 1) {  // ��ȿ ������ ���� 1��
                if (node == node->parent->left) {  // node�� �θ��� �����ڽ��̶��
                        if (keyCount23(node->parent->middle) == 2) { // ���� �θ��� �߰����� 2���� �ڽ��� �����ٸ�
								// delete�� ��带 ������� sibling & parent�� ��ȿ ������ ������ �ľ��Ͽ� balancing �ϰ� 
								// merge || redistribute�� �����Ѵ�.
                                node->small = node->parent->small;
                                node->middle = node->parent->middle->left;
                                node->parent->small = node->parent->middle->small;
                                node->parent->middle->left = node->parent->middle->middle;
                                node->parent->middle->small = node->parent->middle->large;
                                node->parent->middle->middle = node->parent->middle->right;
                                node->parent->middle->large = 0;
                                node->parent->middle->right = NULL;
                                return tree;
                        }
                        if (keyCount23(node->parent->middle) == 1) {
                                node->parent->middle->right = node->parent->middle->middle;
                                node->parent->middle->large = node->parent->middle->small;
                                node->parent->middle->middle = node->parent->middle->left;
                                node->parent->middle->small = node->parent->small;
                                node->parent->middle->left = node->left;
                                node->parent->small = 0;
                                node->parent->left = node->parent->middle;
                                node->parent->middle = NULL;
                                fixNode23(tree, node->parent);
                                return tree;
                        }
                }
                if (node == node->parent->middle) {  // ��尡 �θ��� �߰��ڽ��� ���
                        if (keyCount23(node->parent->left) == 2) {
                                node->middle = node->left;
                                node->small = node->parent->small;
                                node->left = node->parent->left->right;
                                node->parent->small = node->parent->left->large;
                                node->parent->left->right = NULL;
                                node->parent->left->large = 0;
                                return tree;
                        }
                        if (keyCount23(node->parent->left) == 1) {
                                node->parent->left->large = node->parent->small;
                                node->parent->left->right = node->left;
                                node->parent->small = 0;
                                node->parent->middle = NULL;
                                fixNode23(tree, node->parent);
                                return tree;
                        }
                }
        }
        if (keyCount23(node->parent) == 2) {  // �θ� 2���� ��ȿ�����͸� �������
                if (node == node->parent->left) {
                        if (keyCount23(node->parent->middle) == 2) {
                                node->small = node->parent->small;
                                node->middle = node->parent->middle->left;
                                node->parent->small = node->parent->middle->small;
                                node->parent->middle->left = node->parent->middle->middle;
                                node->parent->middle->small = node->parent->middle->large;
                                node->parent->middle->middle = node->parent->middle->right;
                                node->parent->middle->large = 0;
                                node->parent->middle->right = NULL;
                                return tree;
                        }
                        if (keyCount23(node->parent->right) == 2) {
                                node->small = node->parent->small;
                                node->middle = node->parent->middle->left;
                                node->parent->small = node->parent->middle->small;
                                node->parent->middle->left = node->parent->middle->middle;
                                node->parent->middle->small = node->parent->large;
                                node->parent->middle->middle = node->parent->right->left;
                                node->parent->large = node->parent->right->small;
                                node->parent->right->left = node->parent->right->middle;
                                node->parent->right->small = node->parent->right->large;
                                node->parent->right->middle = node->parent->right->right;
                                node->parent->right->large = 0;
                                node->parent->right->right = NULL;
                                return tree;
                        } else {
                                node->small = node->parent->small;
                                node->middle = node->parent->middle->left;
                                node->large = node->parent->middle->small;
                                node->right = node->parent->middle->middle;
                                node->parent->small = node->parent->large;
                                node->parent->middle = node->parent->right;
                                node->parent->large = 0;
                                node->parent->right = NULL;
                                return tree;
                        }
                }
                if (node == node->parent->middle) {
                        if (keyCount23(node->parent->left) == 2) {
                                node->small = node->parent->small;
                                node->middle = node->left;
                                node->left = node->parent->left->right;
                                node->parent->small = node->parent->left->large;
                                node->parent->left->right = NULL;
                                node->parent->left->large = 0;
                                return tree;
                        }
                        if (keyCount23(node->parent->right) >= 1) {
                                node->parent->left->large = node->parent->small;
                                node->parent->left->right = node->left;
                                node->parent->small = node->parent->large;
                                node = node->parent->right;
                                node->parent->large = 0;
                                node->parent->right = NULL;
                                return tree;
                        }
                }
                if (node == node->parent->right) {
                        if (keyCount23(node->parent->middle) == 2) {
                                node->middle = node->left;
                                node->small = node->parent->large;
                                node->left = node->parent->middle->right;
                                node->parent->large = node->parent->middle->large;
                                node->parent->middle->right = NULL;
                                node->parent->middle->large = 0;
                                return tree;
                        } else {
                                node->parent->middle->large= node->parent->large;
                                node->parent->middle->right = node->left;
                                node->parent->large = 0;
                                node->parent->right = NULL;
                                return tree;
                        }
                }
        }
        return NULL;
}

/* 2-3��忡�� ������ ��带 Ʈ������ ������Ų��. */
void destroy23(node23* node)
{
        if(node){
                if (node->parent){  // �θ� �����Ҷ�, �ش� ����� ��ġ�� �θ�� ���� �����Ͽ� ������ ���������.
                        if (node == node->parent->left) node->parent->left = NULL;
                        if (node == node->parent->middle) node->parent->middle = NULL;
                        if (node == node->parent->right) node->parent->right = NULL;
                }
				// �θ� �������� ������ �ش� node�� �����ڽ��� ���������.
                if (node->left) node->left = NULL;
                if (node->middle) node->middle = NULL;
                if (node->right) node->right = NULL;
				// node�� �ּҸ� NULL�� ������Ų��.
                node = NULL;
        }
}

/* 2-3tree�� ���̼����� queue�� �̿��� ��� */        
void print23(tree23* tree){
	  if(tree && tree->root) depthFirstPrint23(tree->root);
}

void depthFirstPrint23(node23* node){

		node23* temp;
        queue* nodeQueue = createQueue(); // queue ����
        enqueue(nodeQueue, node);  // queue�� node�� ����(Tree���� �ֻ��� ������ ���������� ����)
        while (nodeQueue->tail) {  // ���Ե� node�� ����� queue�� empty�� �ɶ����� ����
			    temp = dequeue(nodeQueue);  // node�� ���� temp�� ����Ų��.
                printNode23(temp);  // temp���� �����͸� ���
                if (temp->left) enqueue(nodeQueue, temp->left);  // temp�� �������� �����ڽ��� �ٽ� queue�� ����
                if (temp->middle) enqueue(nodeQueue, temp->middle);
                if (temp->right) enqueue(nodeQueue, temp->right);
        }
}


void printNode23(node23* node){

        int a, b;
        a = b = 0;
		// ��ȿ �����͸� ���� node�� �����͸� ���� �� ���
        if (node->small) a = node->small;
        if (node->large) b = node->large;
        printf("small: %d large: %d\n", a, b);
}