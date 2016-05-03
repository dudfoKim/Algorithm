#pragma once 

#include <stdlib.h>
#include <time.h>
#include "Global.h"
#define MaxSize 30000
#define SYS_MAX_RAND 32767

typedef struct _RandomGen RandomGen;

RandomGen * RandomGen_new ();//�־��� ũ�� ���� (0 ~ (maxSize-1)) ������ ������ ��� ��ü ����
void RandomGen_free (RandomGen * _this);//��ü �Ҹ�
unsigned long RandomGen_number (RandomGen * _this);//(0 ~ (maxSize-1)) ������ ���� �ϳ��� ��´�
double RandomGen_probability (RandomGen * _this);//������ Ȯ���μ�, 0�� 1 ������ double ���� �Ǽ��� ��´�.