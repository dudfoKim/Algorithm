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
	// �ʿ��ϸ� ���⸦ �����ϰ� �� ä��ÿ�.
public:
	App::App ();
	//App::~App ();
	void run ();
	char inputAction ();
	void showAll ();
	void outputMsg_Ending ();
	void outputMsg_Starting ();


// �����Լ����� ���⿡ ����
};

