#include "StableMatch.h"
#include "Timer.h"

void main()
{
	StableMatch*match ; 
	int testSize;
	Timer * timer ;
	double duration ;
	timer = Timer_new() ;

	for ( testSize= 1000 ; testSize<= 5000 ; testSize+= 1000 )
	{
		match = StableMatch_new() ;
		StableMatch_generateTestData(match, testSize);
		Timer_start(timer) ; 
	
		StableMatch_runGS(match) ;
		Timer_stop(timer) ;
		duration = Timer_duration(timer) ;
		StableMatch_showPerformanceMeasure(match, duration);
		StableMatch_free(match) ;
	}

	Timer_free(timer) ;

	printf("Stable Mathcing을종료합니다.\n") ;
} //end of main()