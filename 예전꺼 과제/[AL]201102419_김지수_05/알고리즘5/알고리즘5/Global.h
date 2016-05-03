#pragma once
#include <stdio.h>
typedef int Cost ;
typedef int Vertex ;
typedef struct 
{
	Vertex fromV ;
	Vertex toV ;
	Cost cost ;
}Edge ;