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

int isLeaf(node23* node){  // Node가 Leaf인지 Check
        if (!node->left && !node->middle && !node->right) {
                return 1;  // Left = return 1
        } else {
                return 0;
        }
}

node23* target23(node23* node, int key){  // Key를 넣을 Target Node를 찾는다
        node23* newNode = NULL;
        if (isLeaf(node)) return node;  // Leaf node이면 해당노드를 리턴
        if (key == node->small || key == node->large) return NULL;  // Key가 존재하면 NULL 반환
        if (keyCount23(node) == 1){  // node의 data가 1개이면(=Only exist small data)
				// 왼쪽 자식이 존재하고,  small값보다 key가 작을때 = 왼쪽자식에서 target 재시작
                if (key < node->small && node->left) newNode = target23(node->left, key);
				// 중간 자식이 존재하고, small값보단 클때
                if (key > node->small && node->middle) newNode = target23(node->middle, key);
        }
		else{  // node의 데이터가 2개(=즉, small, large값 둘다 존재)
                if (key < node->small && node->left) newNode = target23(node->left, key);
                if (key > node->small && key < node->large && node->middle) newNode = target23(node->middle, key);
				// 오른쪽 자식이 존재하고, large값보다 클때
                if (key > node->large && node->right) newNode = target23(node->right, key);
        }
        return newNode;  // targer node를 반환
}

node23* search23(node23* node, int key){  // target23()함수과 구조는 비슷하지만 반환값 & if문의 정의는 다르다.
        node23* newNode = NULL;
		// key를 찾으면 해당 node를 반환한다.
        if(key == node->small || key == node->large) return node;
        else if(isLeaf(node)) return NULL;  // leaf노드면 key가 존재하지 않으므로 NULL 반환
        if(!node->large){  // node->large값이 존재하면  
                if (key < node->small && node->left) newNode = search23(node->left, key);
                if (key > node->small && node->middle) newNode = search23(node->middle, key);
        }
		else{ // node->large값이 존재하지 않으면
                if (key < node->small && node->left) newNode = search23(node->left, key);
                if (key > node->small && key < node->large && node->middle) newNode = search23(node->middle, key);
                if (key > node->large && node->right) newNode = search23(node->right, key);
        }
        return newNode;  // target node를 반환
}


int* rearrange(int a, int b, int c){  // 2개의 data를 가진 2-3node에 'Insert' 값이 들어오면 크기순으로 정렬
        int* newTemp = (int*)malloc(sizeof(int)*3);
		int i, j;
        newTemp[0] = a; newTemp[1] = b; newTemp[2] = c;  // 임시저장
        
        for (j=0; j<3; j++)
        for (i=0; i<2; i++){
        int temp;
        if (newTemp[i] > newTemp[i+1]){  // 정렬을 통해 데이터 크기는 오름차순을 이룬다.
                        temp = newTemp[i];
                        newTemp[i] = newTemp[i+1];
                        newTemp[i+1] = temp;
                }
        }
        return newTemp;  // newTemp의 주소반환
}

  // 실질적인 Insert 구현 함수이며, 데이터의 갯수에 따라 Split를 발생시켜
  // 2-3Tree 알고리즘에 따라 위치시킨다.
void insertIntoNode23(tree23* tree, node23* node, int key){
		int* newNode;
        if(isLeaf(node)){  // Leaf node경우
                if (!keyCount23(node)){  // node에 데이터가 존재하지 않을때
                        node->small = key;  // small값에 저장
                }
				else if(keyCount23(node) == 1) {  // 데이터가 1개 존재(=int small)
                        node->large = key;  // large에 저장
                }
				else{  // 2개의 데이터가 존재하는 노드에 Key를 추가로 넣을때(3개 데이터 = Split)
                        newNode = rearrange(node->small, node->large, key);  // 정렬된 데이터를 newNode가 가리킨다.
                        node->small = newNode[0]; node->large = newNode[2];  // 중간값을 제외한 두 데이터를 각각 저장
                        splitLeaf23(tree, node, newNode[1]);  // promoted된 node & data를 가지고 Split를 발생
                }
                return;
        }
		else{  // Leaf node가 아닌경우 key값으로 node를 targeting 한다.
                node23* tempLeaf = target23(node, key);
				// target23() 호출전 임시로 저장된 tempLeaf가 가리키는 노드 & key로 재귀탐색 구현
                if(tempLeaf) insertIntoNode23(tree, tempLeaf, key); 
                return;
        }
}

void splitLeaf23(tree23* tree, node23* node, int key)  // Leaf node에서 Split이 발생할때 호출되는 함수
{
		int newKey=0;  // Key의 임시저장
        if (isLeaf(node)){  // Leaf node일때
                if(!node->parent){  // node의 parent의 값이 없는경우(=Tree에 Node가 1개 존재할때 split이 일어난 경우)
                        node23* newChild = makeNode23();  // 새로운 자식노드 생성
                        node23* newRoot = makeNode23();  // 새로운 루트노드 생성
						// 기본 알고리즘은 Split이 일어난 노드의 large값을 새로운 자식노드의 small값으로 옮기고
						// 새로운 루트노드의 key값을 split값(3개의 데이터의 중간값)을 가지며, 왼쪽 자식은 기존노드, 중간노드는 새 자식노드로 연결
						// 기존의 Root를 newRoot의 node로 대체한다.
                        newChild->small = node->large; node->large = 0; newChild->parent = node->parent = newRoot;
                        newRoot->small = key; newRoot->left = node; newRoot->middle = newChild;
                        tree->root = newRoot;  // Tree->root는 newRoot를 가리킨다.(Root의 교체)
                        return;
                }
                if(node->parent){  // parent가 존재(=다수의 Node를 가진 Tree에서 parent를 가지는 leaf 노드가 Split한 경우)
                        node23* newChild = makeNode23();  // 새로운 자식노드 생성
                        newChild->small = node->large; node->large = 0;  // Leaf node의 large값을 새로운 자식의 small값으로 넣고 초기화(0)
                        if(keyCount23(node->parent) == 1){  // Node의 parent의 데이터 갯수가 1개 일때(=small, 1-2Node)
                                if (key < node->parent->small){  // 부모의 small값보다 key가 작을경우
									  // key를 저장하기 위해 각 데이터 및 자식연결을 오른쪽으로 한단계 이동
                                        node->parent->right = node->parent->middle;
                                        node->parent->large = node->parent->small;
									  // 중간자식을 새로운 자식노드로 연결
                                        node->parent->middle = newChild;
									  // newChild의 parent는 node의 parent와 같으므로 저장
                                        newChild->parent = node->parent;
									  // key값 저장
                                        node->parent->small = key;
                                        return;
                                }
                                if(key > node->parent->small){  // key이 small값보다 클때(현재 large값은 없다)
                                        node->parent->right = newChild;
                                        newChild->parent = node->parent;
                                        node->parent->large = key;
                                        return;
                                }
                        }
                        if(keyCount23(node->parent) == 2){  // parent node에 데이터가 2개 존재할 경우 (2-3 Node)
							    /** 기본 알고리즘은 위와 동일하나 데이터(Large)의 값이 존재하므로 조건문이 1개 더 추가되어 구현된다. **/
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
  /* Leaf node가 아닌 Tree의 중간노드에서 Split가 일어난 경우                                                              
     데이터는 Leaf node를 기준으로 insert 되므로, 해당 Split은 insert로 생긴 splitLeaf23()로부터 발생되었다. */
void splitNode23(tree23* tree, node23* node, node23* newChild, int key)
{
	    int newKey=0;
        if (!node->parent) {  // parent node가 없는 Tree내의 단일 노드인 경우(위 splitLeaf23()의 한 조건과 동일)
                node23* newRoot = makeNode23();
                newRoot->small = key;
                newRoot->left = node; newRoot->middle = newChild;
                node->parent = newChild->parent = newRoot;
                tree->root = newRoot;
                return;
        }
        if (keyCount23(node->parent) == 1) {  // parent의 데이터가 1개인 경우(=1-2 Node), (위 splitLeaf23() 과 동일)
                if (key < node->parent->small) {  // small값보다 작을때
                        node->parent->right = node->parent->middle;
                        node->parent->large = node->parent->small;
                        node->parent->middle = newChild;
                        newChild->parent = node->parent;
                        node->parent->small = key;
                        return;
                }
                if (key > node->parent->small) {  // small값보다 클때
                        node->parent->right = newChild;
                        newChild->parent = node->parent;
                        node->parent->large = key;
                        return;
                }
        }
        if (keyCount23(node->parent) == 2) {  // parent의 데이터가 2개 존재하는 경우(=2-3Node)
                node23* newNode = makeNode23();
                if (key < node->parent->small) {
					// 기본알고리즘은 splitLeaf23과 동일하게 key값을 저장하기 위해 data와 child link를 해당 위치로 한단계 이동하며,
					// parent의 데이터 혹은 key값을 newKey에 저장한 후 다시 Split가 발생될 parent node에서 Promoted된 이 값으로 반복적 Split를 발생시킨다.
                        newNode->left = node->parent->middle; newNode->small = node->parent->large; newNode->middle = node->parent->right;
                        node->parent->middle = newChild; newChild->parent = node->parent; node->parent->large = 0; node->parent->right = NULL;
                        newKey = node->parent->small; node->parent->small = key;
                        splitNode23(tree, node->parent, newNode, newKey);
                        return;
                }
                if (key > node->parent->small && key < node->parent->large) {  // small < key < large 경우
                        newNode->left = newChild; newChild->parent = newNode; newNode->small = node->parent->large; newNode->middle = node->parent->right;
                        node->parent->large = 0; node->parent->right = NULL;
                        // promoted key = key(중간값)
						newKey = key; 
                        splitNode23(tree, node->parent, newNode, newKey);
                        return;
                }
                if (key > node->parent->large) {  // small < large < key 경우
                        newNode->left = node->parent->right; newNode->small = key; newNode->middle = newChild;
                        newChild->parent = newNode;
                        node->parent->right = NULL;
						// promoted key = parent->large(중간값)
                        newKey = node->parent->large; node->parent->large = 0;
                        splitNode23(tree, node->parent, newNode, newKey);
                        return;
                }
        }
}
                                                                
void insert23(tree23* tree, int key){  // Key값을 Insert할때 처음 호출되는 함수

	    node23* newNode;
        if (tree->root) insertIntoNode23(tree, tree->root, key);  // Leaf Node가 아닌경우 탐색 & 삽입 과정을 재수행
        if (!tree->root) {  // Leaf Node인 경우
                newNode = makeNode23();
                tree->root = newNode;  // Leaf node일 경우, Root를 할당한 새로운 노드를 가리키게 만든다.
												// 이는 Tree내의 Node가 Empty상태일때 일어나며 Insert Key를 Tree에 저장하는
												// insert23()이 호출된다.
                insert23(tree, key);
                return;
        }
}

// 삭제할 Key를 Rucursion형식으로 부분함수를 취해 successor Key로 대체한 후 삭제를 수행
node23* successor(node23* node, int key){  

        if (key != node->small && key != node->large){  // node에 Key값이 없을때 NULL 리턴
                return NULL;
        }
        if (key == node->small) {  // small값에 key값이 있을경우 중간자식을 리턴
                return node->middle;
        }
        if (key == node->large) {
                return node->right;
        }
		return 0;
}

// 위의 successor함수를 모티브로 Recursive를 구현하여 대체될 Key를 찾는다.
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

int keyCount23(node23* node){  // node의 유효 데이터수를 산출

		int n = 0;
        if (!node) return 0;
        if (node->small) n++;
        if (node->large) n++;
        return n;
}                                        

node23* deleteNode23(tree23* tree, node23* node, int key){  // key값을 찾은 후 delete 구현

        if (!isLeaf(node)){
                node23* match = search23(node, key);  // key값을 가진 node를 math가 가리킨다.
                if (match) {  // key값이 존재하면 계승할 자식노드를 Recursive하게 탐색하여 해당 node의 데이터값을 변경한다.
                        swapWithSuccessorRecursive(match, key);
                        deleteNode23(tree, match, key);  // 단말노드까지 위 두 함수를 재귀호출
                        return node;  // node는 key
                } else {
                        return NULL;  // 삭제할 key가 존재하지 않으면 NULL 리턴
                }
        } 
		else {  // 단말노드일 경우 key값을 삭제하고 삭제된 위치에 다른 데이터로 대체한다.
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
                        if (!node->parent){ // parent가 NULL일때, key를 삭제하면 Tree는 empty가 되며 null을 반환
                                tree->root = NULL;
                                return NULL;
                        }
						// parent가 존재할 경우 알고리즘은 key값을 삭제하면 삭제될 node를 잡고 있으면서 parent와 parent의 child의 데이터 갯수를 
						// 산출하여 node를 유지하면서 key, child link를 이동시킨다.
                        if (keyCount23(node->parent) == 1) {  // 데이터를 1개 가지고 있는 경우 : redistribute 수행
                                if (key < node->parent->small) {  // key < small일때
										// 부모의 small값을 node로 가져온 후 부모중간자식의 small데이터로 대체
                                        node->small = node->parent->small;
                                        node->parent->small = node->parent->middle->small;
										// 부모의 중간자식의 유효데이터가 2개 존재할 경우
                                        if (keyCount23(node->parent->middle) == 2){
												// 부모의 small로 가져온 중간자식의 small의 자리를 large의 데이터로 대체한 후 large 초기화(0)
                                                node->parent->middle->small = node->parent->middle->large;
                                                node->parent->middle->large = 0;
												// 벨런싱되었으므로 해당 노드 return
                                                return node;
                                        }
										// 중간자식의 데이터가 1개인 경우, 그 데이터를 node로 가져온 후 중간자식을 없앤 후 parent부터 fixing 한다.
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
                        } else if (keyCount23(node->parent) == 2) {  // 부모의 데이터가 2개인 경우 : merge를 수행
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

void delete23(tree23* tree, int key)  // 트리와 트리안의 node가 존재할때 실행
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
        if (keyCount23(node->parent) == 1) {  // 유효 데이터 갯수 1개
                if (node == node->parent->left) {  // node가 부모의 왼쪽자식이라면
                        if (keyCount23(node->parent->middle) == 2) { // 또한 부모의 중간값이 2개의 자식을 가진다면
								// delete된 노드를 기반으로 sibling & parent의 유효 데이터 갯수를 파악하여 balancing 하게 
								// merge || redistribute를 수행한다.
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
                if (node == node->parent->middle) {  // 노드가 부모의 중간자식인 경우
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
        if (keyCount23(node->parent) == 2) {  // 부모가 2개의 유효데이터를 가진경우
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

/* 2-3노드에서 삭제된 노드를 트리내에 삭제시킨다. */
void destroy23(node23* node)
{
        if(node){
                if (node->parent){  // 부모가 존재할때, 해당 노드의 위치를 부모로 부터 산출하여 연결을 끊어버린다.
                        if (node == node->parent->left) node->parent->left = NULL;
                        if (node == node->parent->middle) node->parent->middle = NULL;
                        if (node == node->parent->right) node->parent->right = NULL;
                }
				// 부모가 존재하지 않을때 해당 node의 하위자식을 끊어버린다.
                if (node->left) node->left = NULL;
                if (node->middle) node->middle = NULL;
                if (node->right) node->right = NULL;
				// node의 주소를 NULL로 삭제시킨다.
                node = NULL;
        }
}

/* 2-3tree의 깊이순으로 queue를 이용한 출력 */        
void print23(tree23* tree){
	  if(tree && tree->root) depthFirstPrint23(tree->root);
}

void depthFirstPrint23(node23* node){

		node23* temp;
        queue* nodeQueue = createQueue(); // queue 생성
        enqueue(nodeQueue, node);  // queue에 node를 삽입(Tree내의 최상위 노드부터 순차적으로 삽입)
        while (nodeQueue->tail) {  // 삽입된 node가 저장된 queue가 empty가 될때까지 수행
			    temp = dequeue(nodeQueue);  // node를 꺼내 temp가 가리킨다.
                printNode23(temp);  // temp내의 데이터를 출력
                if (temp->left) enqueue(nodeQueue, temp->left);  // temp를 기준으로 왼쪽자식을 다시 queue에 삽입
                if (temp->middle) enqueue(nodeQueue, temp->middle);
                if (temp->right) enqueue(nodeQueue, temp->right);
        }
}


void printNode23(node23* node){

        int a, b;
        a = b = 0;
		// 유효 데이터를 가진 node의 데이터를 저장 및 출력
        if (node->small) a = node->small;
        if (node->large) b = node->large;
        printf("small: %d large: %d\n", a, b);
}