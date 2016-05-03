#include "Global.h"

typedef struct _UnsortedArrayList UnsortedArrayList;




UnsortedArrayList * UnsortedArrayList_new (int maxsize);
void UnsortedArrayList_free (UnsortedArrayList * _this);
Bool UnsortedArrayList_isEmpty (UnsortedArrayList * _this);
Bool UnsortedArrayList_isFull (UnsortedArrayList * _this);
void UnsortedArrayList_insert (UnsortedArrayList * _this, Element e);
Element UnsortedArrayList_min (UnsortedArrayList * _this);
Element UnsortedArrayList_max (UnsortedArrayList * _this);
Bool UnsortedArrayList_search (UnsortedArrayList * _this, Element key);