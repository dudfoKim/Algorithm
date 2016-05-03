#pragma once
#include "Global.h"
#include "IntervalList.h"
#include "ListIterator.h"

typedef struct _IntervalSchedule IntervalSchedule;

struct _IntervalSchedule
{
	int numOfIntervals;
	Interval interval[100];
	int sortedIndex[100]; // interval[]ÀÇ sorted index
	IntervalList * optimalSet;
};

IntervalSchedule * IntervalSchedule_new();
void IntervalSchedule_free (IntervalSchedule * _this);
Bool IntervalSchedule_inputIntervals (IntervalSchedule * _this);
void IntervalSchedule_runGreedy (IntervalSchedule * _this);
void IntervalSchedule_showResults (IntervalSchedule * _this);