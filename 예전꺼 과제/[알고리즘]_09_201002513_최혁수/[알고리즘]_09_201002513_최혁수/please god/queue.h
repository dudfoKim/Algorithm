#ifndef _queue_h
#define _queue_h
#include "23tree.h"

/* queue및 double linked list의 알고리즘을 결합하여 node를 결합 */
typedef struct queueNode {
        struct queueNode* next;
        struct queueNode* prev;
        node23* object;//
} queueNode;

typedef struct queue {
        queueNode* head;  // queue의 시작
        queueNode* tail;    // queue의 끝
} queue;

queueNode* createQueueNode(node23* object);
queue* createQueue();
queue* enqueue(queue* self, node23* object);
node23* dequeue(queue* self);

#endif