#include "MCST.h"
#include "MCST_MSG.h"

int main()
{
	MCST * mcst;
	mcst=new MCST();

	mcst->showMSG_Starting();
	mcst->inputGraph();
	mcst->findMCST();
	mcst->showResult();

	printf("\n%s\n", MAIN_MSG_END);

	return 0;
}
