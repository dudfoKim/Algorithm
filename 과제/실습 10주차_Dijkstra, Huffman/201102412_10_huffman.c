#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// ������ �ڵ� �˰��� ������ ���� �����

// Ʈ���� ����� ��� ����ü ����
typedef struct TreeNode
{
    int frequency;
	char value;
	char printCode[256];
	struct TreeNode *left;
	struct TreeNode *right;
}Node;

// �켱���� ť�� ����� ��� ����ü ����
typedef struct pq
{
    Node *node;
    struct pq *next;
}pq;

// ������ �ڵ� �˰��� ������ ���� �޼ҵ� ����
pq *insert(Node *node);
Node *pop();
void huffman(int n);
void printQueue();
void printAllCode(Node *node, int n, char *code);

// ������ �ڵ� �˰��� ������ ���� ���� ����
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
	// ���� ����°� �迭�� ���� ���� ���� �� �ʱ�ȭ
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

	// ������� ������ ������ �̸� ����
	fp = fopen("week10.txt", "rt");
	fop = fopen("week10_output.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");
	
		return;
	}

	// �ؽ�Ʈ ���Ͽ��� �о�� ���� �迭 count�� ���� 
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

	// ����ü Node�� �о�� ������ ������ ��, ť�� ����
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
	
	// �켱���� ť�� ���� ����� ���� ����ؼ� Ȯ��
	printf("===== Print the Queue =====\n");
    printQueue();

	// ������ �˰����� ����� Ʈ�� ������ ���� ��, ���� result�� ����
    huffman(num);

	// �� ���ڿ� ���� ������ �ڵ带 ���
	printf("\n===== Print the Huffman Code of char value =====\n");
	printAllCode(result, height, code);

	codeNum--;

	// week10.txt�� �ִ� ��� ���ڿ� ���� �������ڵ带 �ְܼ� week10_output.txt�� ���
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

	// ���� ������� �����ϰ�, �������� �Ҵ��� ������ ���� �޸𸮸� ����
    fclose(fp);
	fclose(fop);

	result = NULL;
	free(result);

	PQ = NULL;
	free(PQ);
}

// �켱���� ť�� ��带 insert�ϴ� �޼ҵ�
pq *insert(Node *node)
{
	// �ӽ÷� ������ �����ϰ�, ���ο� ��带 �Ҵ��ؼ� ���Ḯ��Ʈ ������ ����
    pq *tempNode = NULL;
    pq *newNode = NULL;

    newNode = (pq*) malloc(sizeof(pq));
	newNode->node = node;
    newNode->next = NULL;

	// ť�� �ƹ��͵� ���� ������ �׳� ����
    if(PQ == NULL)
	{
        PQ = newNode;
        return PQ;
	}
	// ���ο� ����� �� ���� ���� ���� ��
	else if(PQ->node->frequency > newNode->node->frequency)
	{
        newNode->next = PQ;
        PQ = newNode;
    }
	// �׷��� ���� ������ 2������ ������ ����
	else
	{
        tempNode = PQ;

		// ť�� ��尡 ���� ��(�� ���� ���� ���� �����鼭)
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
		// ���� ��尡 ����� ������ ��Ʈ�� �ٷ� next�� ���ο� ��带 ����
        if(tempNode->next==NULL)
		{
            tempNode->next = newNode;
		}

        return tempNode;
    }

	return NULL;
}

// �켱���� ť���� ��带 pop�ϴ� �޼ҵ�
Node *pop() 
{
    Node *popNode = NULL;

	popNode = PQ->node;
    PQ = PQ->next;

    return popNode;
}

// ������ �˰����� ������ �����ϴ� �޼ҵ�
void huffman(int n)
{
	int i = 0;

	// �� ����� ������ n���̹Ƿ�, n-2�� �ݺ����� ������ ������ Ʈ���� ����
    for(i=0; i<n-1; i++)
	{
		// �켱���� ť���� pop�� 2���ؼ�, ���� left, right child�� �Ҵ�
		Node *rootNode;
		Node *leftNode = pop();
		Node *rightNode = pop();

		// ���ļ� ���� ��忡 ���� ���� �Ҵ�(���ڴ� R�� ����)
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

// �켱���� ť�� ��� ������ ����ϴ� �޼ҵ�
void printQueue()
{
    pq *printNode = PQ;

    while(printNode!=NULL)
	{
		printf("%c : %d\n", printNode->node->value, printNode->node->frequency);
        printNode = printNode->next;
    }
}

// �� ���ڿ� ���� ������ �ڵ带 ����ϰ�, ������� �����ϴ� �޼ҵ�
void printAllCode(Node *HuffmanNode, int height, char *code)
{
	// Ʈ���� ���̸� �������Ѱ��鼭, left�̸� 0, right�̸� 1�� �Ҵ�
    if(HuffmanNode)
	{
        height++;

        code[height] = '0';
        printAllCode(HuffmanNode->left, height, code);

        code[height] = '1';
        printAllCode(HuffmanNode->right, height, code);

        code[height] = '\0';

		// ���� �����ϰ� ���
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