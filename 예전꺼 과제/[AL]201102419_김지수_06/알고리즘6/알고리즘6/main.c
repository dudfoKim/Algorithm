#include "App.h"

void main()
{
	App * app ;
	app = App_new() ;
	App_inputList(app) ;
	App_sortListByIndex(app) ;
	App_showResults(app) ;
	App_free(app) ;
}