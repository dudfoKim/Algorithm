#include "App.h"

void main()
{
	App * app = App_new() ; // app ��ü�� ����
	App_run(app) ; // app �������
	App_free(app) ; // app ��ü�� �Ҹ�
} //end of main()