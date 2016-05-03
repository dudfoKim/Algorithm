#pragma once

#include "Global.h"
#include "Private.h"

ArrayList * ArrayList_new ();
//�迭 ����Ʈ ��ü�� ���� �迭�� ũ���, �ʱ� ���� ���� �����ϱ�� �Ѵ�.
void ArrayList_free (ArrayList * _this);//��ü �Ҹ�
Bool ArrayList_expandLengthInDouble (ArrayList * _this);//����Ʈ�� ���̸� �� ��� �ø���.//�����ϸ� TRUE, �����ϸ� FALSE�� ��´�.//malloc()�� �������� ��, �ý����� �޸𸮰� ������ �� �ִ�.
Bool ArrayList_isFull (ArrayList * _this);//����Ʈ�� Full �̸� TRUE, �ƴϸ� FALSE�� ��´�.
int ArrayList_length(ArrayList * _this);//����Ʈ�� length�� ��´�.
Bool ArrayList_add (ArrayList * _this, Element e);//���� e�� ����Ʈ�� �����Ѵ�.
Element ArrayList_elementAtIndex (ArrayList * _this, int givenIndex);//����Ʈ�� givenIndex ��° ������ ���� ��´�.