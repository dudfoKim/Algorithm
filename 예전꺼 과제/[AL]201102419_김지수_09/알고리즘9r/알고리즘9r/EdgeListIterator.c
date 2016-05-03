#include "EdgeListIterator.h"




EdgeListIterator * EdgeListIterator_new (EdgeList * edgeList) 
{
	EdgeListIterator * _this = NewObject(EdgeListIterator) ;
	_this->edgelist = edgeList ;
	

	return _this ;
}
void EdgeListIterator_free (EdgeListIterator * _this)
{
	free(_this->curNode);
	free(_this);
}
void EdgeListIterator_begin (EdgeListIterator * _this) 
{
	_this->curNode = _this->edgelist->head->next;
}
Bool EdgeListIterator_end (EdgeListIterator * _this)
{
	if(_this->curNode==NULL);
	{
		return T;
	}
	return F;
}
Edge EdgeListIterator_currentElement (EdgeListIterator * _this)
{
	return _this->curNode->e;

}
void EdgeListIterator_next (EdgeListIterator * _this) 
{
	_this->curNode=_this->curNode->next;
}