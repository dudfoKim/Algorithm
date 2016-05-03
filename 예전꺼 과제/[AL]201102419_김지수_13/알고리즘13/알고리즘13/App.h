#pragma once
#include "Global.h"
#include "PointSet.h"
#include "Pair.h"
#include "FindClosestPair.h"


typedef struct _App App;

struct _App
{
	PointSet * points ;
	FindClosestPair * fcp ;
	Pair * closestPair ;
};

App * App_new();
void App_free (App * _this);
void App_run (App * _this);