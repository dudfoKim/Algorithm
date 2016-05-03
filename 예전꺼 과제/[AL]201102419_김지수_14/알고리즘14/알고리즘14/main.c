#include "WIScheduling.h"


void main()
{
	WIScheduling * wis = WIScheduling_new();
	
	if (!WIScheduling_input(wis)) 
	{
		printf("����: ������ �����ϰ� �Էµ��� �ʾҽ��ϴ�. ���α׷��� �����մϴ�.\n");
	}
	else
	{
		
		WIScheduling_computeP(wis);
		WIScheduling_computeOpt(wis);
		WIScheduling_showResults(wis);
	}
	WIScheduling_free(wis);
	printf("Interval Scheduling�� �����մϴ�.\n");
}