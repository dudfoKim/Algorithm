#pragma once

#include <stdio.h>
#include <stdlib.h>

#define NewObject(TYPE) (TYPE*)malloc(sizeof(TYPE)) 
#define NewVector(TYPE,SIZE) (TYPE*)malloc(sizeof(TYPE)*SIZE)

typedef int Time;
typedef int LectureID;
typedef enum {F, T} Bool;

typedef struct _Interval 
{ 
	Time start ;
	Time finish ; 
}Element ;


