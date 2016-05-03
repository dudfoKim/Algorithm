#include "WIScheduling.h"


void main()
{
	WIScheduling * wis = WIScheduling_new();
	
	if (!WIScheduling_input(wis)) 
	{
		printf("오류: 구간이 적절하게 입력되지 않았습니다. 프로그램을 종료합니다.\n");
	}
	else
	{
		
		WIScheduling_computeP(wis);
		WIScheduling_computeOpt(wis);
		WIScheduling_showResults(wis);
	}
	WIScheduling_free(wis);
	printf("Interval Scheduling을 종료합니다.\n");
}