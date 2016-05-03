#pragma once
#include "Global.h"
#include "Iterator.h"
#include "List.h"

typedef struct _App App;

App * App_new ();
void App_free (App * _this);
void App_run (App * _this);
void App_outputStartingMessage (App * _this);
void App_outputEndingMessage (App * _this);
