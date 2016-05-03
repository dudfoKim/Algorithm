#ifndef _queue_h
#define _queue_h
#include "23tree.h"

/* queue�� double linked list�� �˰����� �����Ͽ� node�� ���� */
typedef struct queueNode {
        struct queueNode* next;
        struct queueNode* prev;
        node23* object;//
} queueNode;

typedef struct queue {
        queueNode* head;  // queue�� ����
        queueNode* tail;    // queue�� ��
} queue;

queueNode* createQueueNode(node23* object);
queue* createQueue();
queue* enqueue(queue* self, node23* object);
node23* dequeue(queue* self);

#endif