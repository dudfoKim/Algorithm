#include "App.h"

void main()
{
	App * app ;
	app = new App() ;
	app->outputMsg_Starting () ;
	app->run() ;
	app->outputMsg_Ending () ;
	delete app ;
}