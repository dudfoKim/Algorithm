#pragma once
#include <stdio.h>
#include <stdlib.h>

#define NewObject(TypeName) (TypeName *)malloc(sizeof(TypeName))
#define NewVector(TypeName,Size) (TypeName *)malloc(sizeof(TypeName)*(Size))

typedef enum {F, T} Bool;
