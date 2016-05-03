#include "App.h"

void main()
{
	App * app ;
	app = App_new() ;
	App_outputStartingMessage(app) ;
	App_run(app) ;
	App_outputEndingMessage(app) ;
	App_free(app) ;
}