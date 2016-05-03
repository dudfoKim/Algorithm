#pragma once

#include "Global.h"
#include "App.h"
#include "Private.h"

ArrayListIter * ArrayListIter_new (ArrayList * list);//객체를 생성한다.
void ArrayListIter_free (ArrayListIter * _this);//객체를 소멸시킨다.
void ArrayListIter_begin (ArrayListIter * _this);//반복자를 리스트의 처음 원소 위치로 설정하여, 반복을 시작한다.
Bool ArrayListIter_endOfList (ArrayListIter * _this);//리스트의 끝인지를 알려준다.
Element ArrayListIter_currentElement (ArrayListIter * _this);//현재 위치의 원소를 얻는다.
void ArrayListIter_next (ArrayListIter * _this);//다음 원소 위치로 반복자를 이동한다.
