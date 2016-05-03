#pragma once

#include <stdio.h>
#include <stdlib.h>

#define NewObject(TYPE) (TYPE*)malloc(sizeof(TYPE)) 
#define NewVector(TYPE,SIZE) (TYPE*)malloc(sizeof(TYPE)*SIZE)

typedef enum {F, T} Bool;
typedef int Element;