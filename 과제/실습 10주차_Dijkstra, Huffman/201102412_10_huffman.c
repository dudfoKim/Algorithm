#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// 허프만 코드 알고리즘 구현을 위한 선언부

// 트리에 사용할 노드 구조체 선언
typedef struct TreeNode
{
    int frequency;
	char value;
	char printCode[256];
	struct TreeNode *left;
	struct TreeNode *right;
}Node;

// 우선순위 큐에 사용할 노드 구조체 선언
typedef struct pq
{
    Node *node;
    struct pq *next;
}pq;

// 허프만 코드 알고리즘 구현을 위한 메소드 선언
pq *insert(Node *node);
Node *pop();
void huffman(int n);
void printQueue();
void printAllCode(Node *node, int n, char *code);

// 허프만 코드 알고리즘 구현을 위한 변수 선언
int i = 0;
int j = 0;
int num = 0;
int codeNum = 1;
int charNum = 1;
int height = -1;
int count[255];
Node *result;
Node *codeNode;
pq *PQ = NULL;

void main()
{
	// 파일 입출력과 배열을 위한 변수 선언 및 초기화
	FILE *fp;
	FILE *fop;

	char data;
	char *code = (char*)malloc(sizeof(char));
	char *value = (char*)malloc(sizeof(char));
	result = (Node*)malloc(sizeof(Node));
	codeNode = (Node*)malloc(sizeof(Node));

	for(i=0; i<255; i++)
	{
		count[i] = 0;
	}

	// 입출력을 실행할 파일의 이름 지정
	fp = fopen("week10.txt", "rt");
	fop = fopen("week10_output.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");
	
		return;
	}

	// 텍스트 파일에서 읽어온 값을 배열 count에 저장 
	while(EOF!=fscanf(fp, "%c", &data))
	{
		value[charNum-1] = data;
		charNum++;
		value = (char*)realloc(value, sizeof(char)*charNum);

		for(i=0; i<255; i++)
		{
			if(data==i)
			{
				count[data]++;
			}
		}
	}

	charNum--;

	// 구조체 Node에 읽어온 값들을 저장한 후, 큐에 삽입
	for(i=0; i<255; i++)
	{
		if(count[i]!=0)
		{
			Node *node = (Node*)malloc(sizeof(Node));
			node->frequency = count[i];
			node->value = i;
			node->left = NULL;
			node->right = NULL;
			insert(node);
			num++;
		}
	}
	
	// 우선순위 큐에 넣은 노드의 값을 출력해서 확인
	printf("===== Print the Queue =====\n");
    printQueue();

	// 허프만 알고리즘의 결과로 트리 구조를 생성 후, 변수 result에 저장
    huffman(num);

	// 각 문자에 대한 허프만 코드를 출력
	printf("\n===== Print the Huffman Code of char value =====\n");
	printAllCode(result, height, code);

	codeNum--;

	// week10.txt에 있는 모든 문자에 대한 허프만코드를 콘솔과 week10_output.txt에 출력
	printf("\n===== Print the all code =====\n");	

	for(i=0; i<charNum; i++)
	{
		for(j=0; j<codeNum; j++)
		{
			if(value[i]==codeNode[j].value)
			{
				printf("%s (%c)\n", codeNode[j].printCode, codeNode[j].value);
				fprintf(fop, "%s", codeNode[j].printCode, codeNode[j].value);
			}
		}
	}

	// 파일 입출력을 종료하고, 동적으로 할당한 변수에 대한 메모리를 해제
    fclose(fp);
	fclose(fop);

	result = NULL;
	free(result);

	PQ = NULL;
	free(PQ);
}

// 우선순위 큐에 노드를 insert하는 메소드
pq *insert(Node *node)
{
	// 임시로 변수를 선언하고, 새로운 노드를 할당해서 연결리스트 구조를 생성
    pq *tempNode = NULL;
    pq *newNode = NULL;

    newNode = (pq*) malloc(sizeof(pq));
	newNode->node = node;
    newNode->next = NULL;

	// 큐에 아무것도 없을 때에는 그냥 생성
    if(PQ == NULL)
	{
        PQ = newNode;
        return PQ;
	}
	// 새로운 노드의 빈도 수가 제일 작을 때
	else if(PQ->node->frequency > newNode->node->frequency)
	{
        newNode->next = PQ;
        PQ = newNode;
    }
	// 그렇지 않을 때에는 2가지로 나눠서 삽입
	else
	{
        tempNode = PQ;

		// 큐에 노드가 있을 때(빈도 수가 제일 작지 않으면서)
        while(tempNode->next!=NULL)
		{
			if(tempNode->next->node->frequency <= newNode->node->frequency)
			{
                tempNode = tempNode->next;
			}
            else
			{
                newNode->next = tempNode->next;
                tempNode->next = newNode;
                break;
            }
        }
		// 다음 노드가 비었을 때에는 루트의 바로 next에 새로운 노드를 삽입
        if(tempNode->next==NULL)
		{
            tempNode->next = newNode;
		}

        return tempNode;
    }

	return NULL;
}

// 우선순위 큐에서 노드를 pop하는 메소드
Node *pop() 
{
    Node *popNode = NULL;

	popNode = PQ->node;
    PQ = PQ->next;

    return popNode;
}

// 허프만 알고리즘을 실제로 구현하는 메소드
void huffman(int n)
{
	int i = 0;

	// 총 노드의 갯수가 n개이므로, n-2번 반복문을 돌려서 허프만 트리를 생성
    for(i=0; i<n-1; i++)
	{
		// 우선순위 큐에서 pop을 2번해서, 각각 left, right child로 할당
		Node *rootNode;
		Node *leftNode = pop();
		Node *rightNode = pop();

		// 합쳐서 만든 노드에 대한 값을 할당(문자는 R로 통일)
        rootNode = (Node*) malloc(sizeof(Node));
		rootNode->value = 'R';
        rootNode->left = leftNode;
        rootNode->right = rightNode;
        rootNode->frequency = leftNode->frequency + rightNode->frequency;
        insert(rootNode);

        printf("\n===== Print the current tree =====\n");
		printQueue();
    }

    result = pop();
}

// 우선순위 큐의 노드 내용을 출력하는 메소드
void printQueue()
{
    pq *printNode = PQ;

    while(printNode!=NULL)
	{
		printf("%c : %d\n", printNode->node->value, printNode->node->frequency);
        printNode = printNode->next;
    }
}

// 각 문자에 대한 허프만 코드를 출력하고, 결과값을 저장하는 메소드
void printAllCode(Node *HuffmanNode, int height, char *code)
{
	// 트리의 높이를 증가시켜가면서, left이면 0, right이면 1을 할당
    if(HuffmanNode)
	{
        height++;

        code[height] = '0';
        printAllCode(HuffmanNode->left, height, code);

        code[height] = '1';
        printAllCode(HuffmanNode->right, height, code);

        code[height] = '\0';

		// 값을 저장하고 출력
		if(HuffmanNode->left == NULL || HuffmanNode->right == NULL)
		{
			codeNode[codeNum-1].value = HuffmanNode->value;
			strcpy(codeNode[codeNum-1].printCode, code);
			codeNode[codeNum-1].left = NULL;
			codeNode[codeNum-1].right = NULL;
			codeNode[codeNum-1].frequency = 0;
			codeNum++;
			codeNode = (Node*)realloc(codeNode, sizeof(Node)*codeNum);
			printf("%c : %s\n", codeNode[codeNum-2].value, codeNode[codeNum-2].printCode);
		}
    }
}