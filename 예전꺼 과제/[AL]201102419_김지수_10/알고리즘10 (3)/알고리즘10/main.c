#include "StableMatch.h"

void main()
{
	StableMatch * match ;
	match = StableMatch_new() ;
	if (! StableMatch_input(match)) 
	{
		printf("����: �����ϰ��Էµ����ʾҽ��ϴ�. ���α׷��������մϴ�.\n");
	}

	else 
	{
		
		StableMatch_runGS(match) ;
		StableMatch_showResults(match) ;
	}

	StableMatch_free(match) ;
	printf("Stable Mathcing�������մϴ�.\n") ;
} //end of main()