#pragma once

#include "Global.h"
#include "ArrayList.h"
#include "ArrayListIter.h"
#include "IndexList.h"
#include "IndexListIter.h"

typedef struct _App App ;

struct _App 
{
	int numOfElements ;
	ArrayList * list ;
	IndexList * indexList ;
};

App * App_new();
void App_free(App * _this);
Bool App_inputList (App * _this);
void App_sortListByIndex (App * _this);
void App_showResults (App * _this);
