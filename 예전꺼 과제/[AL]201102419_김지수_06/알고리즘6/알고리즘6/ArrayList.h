#pragma once

#include "Global.h"
#include "Private.h"

ArrayList * ArrayList_new ();
//배열 리스트 객체를 생성 배열의 크기는, 초기 설정 값을 지정하기로 한다.
void ArrayList_free (ArrayList * _this);//객체 소멸
Bool ArrayList_expandLengthInDouble (ArrayList * _this);//리스트의 길이를 두 배로 늘린다.//성공하면 TRUE, 실패하면 FALSE를 얻는다.//malloc()를 실행했을 때, 시스템의 메모리가 부족할 수 있다.
Bool ArrayList_isFull (ArrayList * _this);//리스트가 Full 이면 TRUE, 아니면 FALSE를 얻는다.
int ArrayList_length(ArrayList * _this);//리스트의 length를 얻는다.
Bool ArrayList_add (ArrayList * _this, Element e);//원소 e를 리스트에 삽입한다.
Element ArrayList_elementAtIndex (ArrayList * _this, int givenIndex);//리스트의 givenIndex 번째 원소의 값을 얻는다.