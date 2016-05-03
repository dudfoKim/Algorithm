#pragma once
#include "Global.h"

typedef struct _UnsortedArrayPQ UnsortedArrayPQ;

UnsortedArrayPQ * UnsortedArrayPQ_new (int maxsize);
void UnsortedArrayPQ_free (UnsortedArrayPQ * _this);
Bool UnsortedArrayPQ_isEmpty (UnsortedArrayPQ * _this);
Bool UnsortedArrayPQ_isFull (UnsortedArrayPQ * _this);
void UnsortedArrayPQ_insert (UnsortedArrayPQ * _this, Element e);
Element UnsortedArrayPQ_deleteMin (UnsortedArrayPQ * _this);