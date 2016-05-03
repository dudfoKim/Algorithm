#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queueNode* createQueueNode(node23* object){  // Init & alloc QueueNode

        queueNode* newQueue = (queueNode*)malloc(sizeof(queueNode));
        newQueue->next = newQueue->prev = NULL;
        newQueue->object = object;
        return newQueue;
}

queue* createQueue(){  // Init & alloc Queue

        queue* newQueue = (queue*)malloc(sizeof(queue));
        newQueue->head = newQueue->tail = NULL;
        return newQueue;
}

/* Queue���� node23�� �����ͷ� �����Ѵ�. */
/* ���Ե� �����ʹ� head�� ���� ����ǰ� �����. */
queue* enqueue(queue* self, node23* object){
	// node�� ���� QueueNode�� ���� �� temp�� ����Ų��.
	queueNode* temp = createQueueNode(object);
        if (!self->head || !self->tail) {  // head, tail�� ���� NULL�϶�(empty Queue)
                self->head = self->tail = temp;  // temp�� ����Ų��.
        }
		else{  // �̹� ���Ե� Node�� ������ ���
			    // Double linked list �������� ���� ����� node�� ���� node�� ����
                temp->next = self->head;
                self->head->prev = temp;
                self->head = temp;
        }
        return self;
}

/* Queue���� node23�� �����ͷ� ��ȯ�Ѵ�. */
node23* dequeue(queue* self){

		node23* object; // �ӽ��� ��带 ����Ų��.
		  // Queue�� FIFO(���Լ���)������ ������ tail�� ����Ű�� QueueNode�� ���Ե� �������̴�.
	    queueNode* QueueNode = self->tail;
        if (self->tail) {
                if (!self->tail->prev) {
                        self->head = self->tail = NULL;
                } else {
                        self->tail = self->tail->prev;
                }
        }
        
        object = QueueNode->object;
        free(QueueNode);  // QueueNode �޸� ����
        
        return object;
}