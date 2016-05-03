#pragma once

#include "Global.h"
#include "App.h"
#include "Private.h"

ArrayListIter * ArrayListIter_new (ArrayList * list);//��ü�� �����Ѵ�.
void ArrayListIter_free (ArrayListIter * _this);//��ü�� �Ҹ��Ų��.
void ArrayListIter_begin (ArrayListIter * _this);//�ݺ��ڸ� ����Ʈ�� ó�� ���� ��ġ�� �����Ͽ�, �ݺ��� �����Ѵ�.
Bool ArrayListIter_endOfList (ArrayListIter * _this);//����Ʈ�� �������� �˷��ش�.
Element ArrayListIter_currentElement (ArrayListIter * _this);//���� ��ġ�� ���Ҹ� ��´�.
void ArrayListIter_next (ArrayListIter * _this);//���� ���� ��ġ�� �ݺ��ڸ� �̵��Ѵ�.
