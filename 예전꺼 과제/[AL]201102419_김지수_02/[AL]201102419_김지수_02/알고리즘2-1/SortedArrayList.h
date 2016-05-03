#include "Global.h"

typedef struct _SortedArrayList SortedArrayList;

//typedef enum{FALSE, TRUE} Bool;

SortedArrayList * SortedArrayList_new (int maxsize);
void SortedArrayList_free (SortedArrayList * _this);
Bool SortedArrayList_isEmpty (SortedArrayList * _this);
Bool SortedArrayList_isFull (SortedArrayList * _this);
void SortedArrayList_insert (SortedArrayList * _this, Element e);
Element SortedArrayList_min (SortedArrayList * _this);
Element SortedArrayList_max (SortedArrayList * _this);
Bool SortedArrayList_search (SortedArrayList * _this, Element key);