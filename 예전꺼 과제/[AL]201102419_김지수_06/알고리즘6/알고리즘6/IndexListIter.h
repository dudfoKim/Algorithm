#pragma once

#include "Global.h"
#include "App.h"
#include "Private.h"

IndexListIter * IndexListIter_new (IndexList * list);//��ü�� �����Ѵ�.
void IndexListIter_free (IndexListIter * _this);//��ü�� �Ҹ��Ų��.
void IndexListIter_begin (IndexListIter * _this);//�ݺ��ڸ� ����Ʈ�� ó�� ���� ��ġ�� �����Ͽ�, �ݺ��� �����Ѵ�.
Bool IndexListIter_endOfList (IndexListIter * _this);//����Ʈ�� �������� �˷��ش�.
Element IndexListIter_currentElement (IndexListIter * _this);//���� ��ġ�� ���Ҹ� ��´�.
void IndexListIter_next (IndexListIter * _this);//���� ���� ��ġ�� �ݺ��ڸ� �̵��Ѵ�.