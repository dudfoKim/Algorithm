#pragma once

#include "Global.h"
#include "ArrayList.h"
#include "Private.h"

IndexList * IndexList_new ();//객체를 생성한다.
IndexList * IndexList_newBySortingIndex(ArrayList * list);//주어진 리스트의 index list를 생성하고, 그 index list를 sort한다.
void IndexList_free (IndexList * _this);//객체를 소멸시킨다.
void IndexList_sortByIndex (IndexList * _this);