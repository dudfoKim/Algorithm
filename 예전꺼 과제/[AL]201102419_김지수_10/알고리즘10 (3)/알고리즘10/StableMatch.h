#pragma once
#include "Global.h"
#include "LinkedList.h"

typedef struct _StableMatch StableMatch;

struct _StableMatch
{
	int numOfPairs;
	int **manPref;
	int **womanPref;
	LinkedList * freeMan;
	int *nex;
	int *current;
	int **ranking;
};


StableMatch* StableMatch_new();
void StableMatch_free(StableMatch* _this);
Bool StableMatch_input(StableMatch* _this);
void StableMatch_runGS(StableMatch* _this);
void StableMatch_showResults(StableMatch* _this);
void StableMatch_initGS(StableMatch* _this);