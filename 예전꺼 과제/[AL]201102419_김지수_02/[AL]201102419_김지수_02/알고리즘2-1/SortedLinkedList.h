#include "Global.h"

typedef struct _Node Node;
typedef struct _SortedLinkedList SortedLinkedList;

SortedLinkedList * SortedLinkedList_new ();
void SortedLinkedList_free (SortedLinkedList * _this);
Bool SortedLinkedList_isEmpty (SortedLinkedList * _this);
Bool SortedLinkedList_isFull (SortedLinkedList * _this);
void SortedLinkedList_insert (SortedLinkedList * _this, Element e);
Element SortedLinkedList_min (SortedLinkedList * _this);
Element SortedLinkedList_max (SortedLinkedList * _this);
Bool SortedLinkedList_search (SortedLinkedList * _this, Element key);
