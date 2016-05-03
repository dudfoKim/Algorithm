#pragma once
#include "Global.h"

typedef int Edge;
typedef struct _MinHeapPQ MinHeapPQ;


	// array for a complete binary tree
MinHeapPQ * MinHeapPQ_new (int maxsize);
void MinHeapPQ_free (MinHeapPQ * _this);
Bool MinHeapPQ_isEmpty (MinHeapPQ * _this);
Bool MinHeapPQ_isFull (MinHeapPQ * _this);
Bool MinHeapPQ_insert (MinHeapPQ * _this, Edge e);
Edge MinHeapPQ_deleteMin (MinHeapPQ * _this);
	
	
