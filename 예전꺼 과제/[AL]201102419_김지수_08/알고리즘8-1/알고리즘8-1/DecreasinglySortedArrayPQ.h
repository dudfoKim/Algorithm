#pragma once
#include "Global.h"

typedef struct _DecreasinglySortedArrayPQ DecreasinglySortedArrayPQ;

//typedef enum{FALSE, TRUE} Bool;

DecreasinglySortedArrayPQ * DecreasinglySortedArrayPQ_new (int maxsize);
void DecreasinglySortedArrayPQ_free (DecreasinglySortedArrayPQ * _this);
Bool DecreasinglySortedArrayPQ_isEmpty (DecreasinglySortedArrayPQ * _this);
Bool DecreasinglySortedArrayPQ_isFull (DecreasinglySortedArrayPQ* _this);
void DecreasinglySortedArrayPQ_insert (DecreasinglySortedArrayPQ * _this, Element e);
Element DecreasinglySortedArrayPQ_deleteMin (DecreasinglySortedArrayPQ * _this);

