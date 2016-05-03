#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef enum {FALSE, TRUE} Bool ;
typedef int PointIndex ;
typedef float Coordinate ;
typedef float Distance ;
#define InfiniteDistance +1.0E30
#define NumOfNeighbors 6

#define NewObject(TypeName) (TypeName *)malloc(sizeof(TypeName))
#define NewVector(TypeName,Size) (TypeName *)malloc(sizeof(TypeName)*(Size))

typedef enum{F, T} Bool;

#define BlanksForSingleIndent " "
#define printfIndentBlanks(IndentCount) for (int i=0; i<IndentCount; i++){printf(BlanksForSingleIndent);}
