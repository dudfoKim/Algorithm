#include "global.h"

typedef struct _WIScheduling WIScheduling;

typedef struct{
	int start;
	int finish;
	int weight;
}WeightedInterval;

struct _WIScheduling{
	int intnumOfIntervals;
	WeightedInterval weightedInterval[100];
	char m[100];
	int p[100];
	char select[100];
	int sumKeep;
};

WIScheduling * WIScheduling_new();
void WIScheduling_free(WIScheduling * _this);
Bool WIScheduling_input(WIScheduling * _this);
void WIScheduling_computeP(WIScheduling* _this);
void WIScheduling_computeOpt(WIScheduling* _this);
int WIScheduling_findSolution(WIScheduling* _this);
void WIScheduling_showResults(WIScheduling* _this);
int WIScheduling_qsort(WIScheduling* _this,int n,int key);