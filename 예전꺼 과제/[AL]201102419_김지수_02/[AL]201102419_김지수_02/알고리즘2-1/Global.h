#pragma once
#include <stdlib.h>//for malloc() 


#define NewObject(TYPE) (TYPE*)malloc(sizeof(TYPE)) 
#define NewVector(TYPE,SIZE) (TYPE*)malloc(sizeof(TYPE)*SIZE)

typedef enum{F, T} Bool;


typedef int Element;