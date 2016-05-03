#pragma once
#include "App_MSG.h"
#include "Global.h"
#include "List.h"
#include "Iterator.h"
class App 
{
private:

	List * list ;
	static char * msg_Starting ;
	static char * msg_Ending ;
	char input;
	// 필요하면 여기를 적절하게 더 채우시오.
public:
	App::App ();
	//App::~App ();
	void run ();
	char inputAction ();
	void showAll ();
	void outputMsg_Ending ();
	void outputMsg_Starting ();


// 공개함수들은 여기에 선언
};

