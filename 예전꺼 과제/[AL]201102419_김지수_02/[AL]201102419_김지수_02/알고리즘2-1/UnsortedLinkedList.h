#include "Global.h"

typedef struct _Node Node;
typedef struct _UnsortedLinkedList UnsortedLinkedList;

UnsortedLinkedList * UnsortedLinkedList_new ();
void UnsortedLinkedList_free (UnsortedLinkedList * _this);
Bool UnsortedLinkedList_isEmpty (UnsortedLinkedList * _this);
Bool UnsortedLinkedList_isFull (UnsortedLinkedList * _this);
void UnsortedLinkedList_insert (UnsortedLinkedList * _this, Element e);
Element UnsortedLinkedList_min (UnsortedLinkedList * _this);
Element UnsortedLinkedList_max (UnsortedLinkedList * _this);
Bool UnsortedLinkedList_search (UnsortedLinkedList * _this, Element key);
