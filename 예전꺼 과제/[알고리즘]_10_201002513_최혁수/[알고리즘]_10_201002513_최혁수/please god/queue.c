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

/* Queue내에 node23을 데이터로 삽입한다. */
/* 삽입될 데이터는 head를 통해 연결되게 만든다. */
queue* enqueue(queue* self, node23* object){
	// node를 가진 QueueNode를 생성 후 temp로 가리킨다.
	queueNode* temp = createQueueNode(object);
        if (!self->head || !self->tail) {  // head, tail가 전부 NULL일때(empty Queue)
                self->head = self->tail = temp;  // temp를 가리킨다.
        }
		else{  // 이미 삽입된 Node가 존재할 경우
			    // Double linked list 개념으로 이전 연결된 node와 삽입 node를 연결
                temp->next = self->head;
                self->head->prev = temp;
                self->head = temp;
        }
        return self;
}

/* Queue내에 node23을 데이터로 반환한다. */
node23* dequeue(queue* self){

		node23* object; // 임시적 노드를 가리킨다.
		  // Queue는 FIFO(선입선출)구조를 가지며 tail이 가리키는 QueueNode가 선입된 데이터이다.
	    queueNode* QueueNode = self->tail;
        if (self->tail) {
                if (!self->tail->prev) {
                        self->head = self->tail = NULL;
                } else {
                        self->tail = self->tail->prev;
                }
        }
        
        object = QueueNode->object;
        free(QueueNode);  // QueueNode 메모리 해제
        
        return object;
}