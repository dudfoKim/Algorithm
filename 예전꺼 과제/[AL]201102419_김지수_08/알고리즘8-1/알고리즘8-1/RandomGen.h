#pragma once 

#include <stdlib.h>
#include <time.h>
#include "Global.h"
#define MaxSize 30000
#define SYS_MAX_RAND 32767

typedef struct _RandomGen RandomGen;

RandomGen * RandomGen_new ();//주어진 크기 범위 (0 ~ (maxSize-1)) 사이의 난수를 얻는 객체 생성
void RandomGen_free (RandomGen * _this);//객체 소멸
unsigned long RandomGen_number (RandomGen * _this);//(0 ~ (maxSize-1)) 사이의 난수 하나를 얻는다
double RandomGen_probability (RandomGen * _this);//무작위 확률로서, 0과 1 사이의 double 형의 실수를 얻는다.