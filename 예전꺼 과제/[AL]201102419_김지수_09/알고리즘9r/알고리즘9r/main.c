#include "Coloring.h"

void main()
{
	Coloring * coloring ;
	printf("<<Coloring을 시작합니다>>\n") ;
	coloring = Coloring_new() ;
	Coloring_inputAndMakeGraph (coloring) ;
	Coloring_showGraph (coloring) ;
	Coloring_runColoring (coloring) ;
	Coloring_showColoring (coloring) ;
	Coloring_free (coloring) ;
	printf("\n<<Coloring을 종료합니다>>\n") ;
} //end of main()