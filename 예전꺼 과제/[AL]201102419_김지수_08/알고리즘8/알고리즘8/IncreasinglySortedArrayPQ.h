#pragma once
#include "Global.h"

typedef struct _IncreasinglySortedArrayPQ IncreasinglySortedArrayPQ;

//typedef enum{FALSE, TRUE} Bool;

IncreasinglySortedArrayPQ * IncreasinglySortedArrayPQ_new (int maxsize);
void IncreasinglySortedArrayPQ_free (IncreasinglySortedArrayPQ * _this);
Bool IncreasinglySortedArrayPQ_isEmpty (IncreasinglySortedArrayPQ * _this);
Bool IncreasinglySortedArrayPQ_isFull (IncreasinglySortedArrayPQ * _this);
void IncreasinglySortedArrayPQ_insert (IncreasinglySortedArrayPQ * _this, Element e);
Element IncreasinglySortedArrayPQ_deleteMin (IncreasinglySortedArrayPQ * _this);

