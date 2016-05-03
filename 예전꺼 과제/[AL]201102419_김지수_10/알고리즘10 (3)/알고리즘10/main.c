#include "StableMatch.h"

void main()
{
	StableMatch * match ;
	match = StableMatch_new() ;
	if (! StableMatch_input(match)) 
	{
		printf("오류: 적절하게입력되지않았습니다. 프로그램을종료합니다.\n");
	}

	else 
	{
		
		StableMatch_runGS(match) ;
		StableMatch_showResults(match) ;
	}

	StableMatch_free(match) ;
	printf("Stable Mathcing을종료합니다.\n") ;
} //end of main()