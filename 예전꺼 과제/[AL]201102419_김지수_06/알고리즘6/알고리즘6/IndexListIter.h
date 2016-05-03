#pragma once

#include "Global.h"
#include "App.h"
#include "Private.h"

IndexListIter * IndexListIter_new (IndexList * list);//객체를 생성한다.
void IndexListIter_free (IndexListIter * _this);//객체를 소멸시킨다.
void IndexListIter_begin (IndexListIter * _this);//반복자를 리스트의 처음 원소 위치로 설정하여, 반복을 시작한다.
Bool IndexListIter_endOfList (IndexListIter * _this);//리스트의 끝인지를 알려준다.
Element IndexListIter_currentElement (IndexListIter * _this);//현재 위치의 원소를 얻는다.
void IndexListIter_next (IndexListIter * _this);//다음 원소 위치로 반복자를 이동한다.