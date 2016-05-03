#pragma once

#include "Global.h"
#include "ArrayList.h"
#include "Private.h"

IndexList * IndexList_new ();//��ü�� �����Ѵ�.
IndexList * IndexList_newBySortingIndex(ArrayList * list);//�־��� ����Ʈ�� index list�� �����ϰ�, �� index list�� sort�Ѵ�.
void IndexList_free (IndexList * _this);//��ü�� �Ҹ��Ų��.
void IndexList_sortByIndex (IndexList * _this);