#include "Coloring.h"

void main()
{
	Coloring * coloring ;
	printf("<<Coloring�� �����մϴ�>>\n") ;
	coloring = Coloring_new() ;
	Coloring_inputAndMakeGraph (coloring) ;
	Coloring_showGraph (coloring) ;
	Coloring_runColoring (coloring) ;
	Coloring_showColoring (coloring) ;
	Coloring_free (coloring) ;
	printf("\n<<Coloring�� �����մϴ�>>\n") ;
} //end of main()