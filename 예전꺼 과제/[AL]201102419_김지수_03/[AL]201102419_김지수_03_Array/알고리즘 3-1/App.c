#include <stdio.h>
#include <stdlib.h>
#include "App.h"

#define MSG_Starting "<List�� ����: Sorted Array>"
#define MSG_Ending "<���α׷��� �����մϴ�>"
#define ACTION_Insert '%'
#define ACTION_DeleteMax '+'
#define ACTION_DeleteMin '-'
#define ACTION_Reset '~'
#define ACTION_Length '#'
#define ACTION_ShowAll '!'
#define ACTION_deleteKth '?'
#define Esc 27

char App_inputAction (App * _this);
void App_showAll (App * _this);

struct _App 
{
	List * list ;
	char * startingMsg ;
	char * endingMsg ;
	char input;
// �ʿ��ϸ� ���⸦ �����ϰ� �� ä��ÿ�.
};

App * App_new (void)
{
	App * _this= NewObject(App) ;
	_this->list = List_new(ArrayListMaxLength) ;
	_this->startingMsg = MSG_Starting ;
	_this->endingMsg = MSG_Ending ;
	

	return _this ;
}

void App_run (App *_this)
{
	char action;
	int input, temp;
	
	printf("\n'/. : ��������, ! : �������, + : �ִ밪����, ? : ���ǻ���, # : ���Ұ�������, - : �ּҰ�����, ~ : ����Ʈ�ʱ�ȭ, ESC : ����\n");
	action =App_inputAction(_this) ;
	while (action != Esc ) 
	{
		if ( action == ACTION_Insert ) 
		{
			printf("\n������ ���ڸ� �Է��ϼ��� : ");
			scanf("%d", &input);
			if(List_doesExist (_this->list, input))
			{
				printf("�̹� �����ϴ� �����Դϴ�!\n");
			}
			else
			{
				List_insert (_this->list, input);
			}
		}
		else if ( action == ACTION_DeleteMax ) 
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n�ִ밪 %d�� �����Ǿ����ϴ�.\n", List_deleteMax (_this->list));
			}
		}
		else if ( action == ACTION_ShowAll ) 
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n����Ʈ�� ���Ҹ� ����մϴ� : ");
				App_showAll(_this);
				printf("\n");
			}
		}
		else if( action == ACTION_DeleteMin)
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n�ּҰ� %d�� �����Ǿ����ϴ�.\n", List_deleteMin (_this->list));
			}
		}

		else if(action == ACTION_Length)
		{
			printf("\n����Ʈ�� ������ ������ %d�� �Դϴ�.\n", List_length(_this->list));
		}
		else if(action == ACTION_Reset)
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				List_reset(_this->list);
				printf("\n����Ʈ�� ������ϴ�.\n");
			}
		}
		else if(action == ACTION_deleteKth )
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n�����ҿ����� index�� �Է��ϼ��� : ");
				scanf("%d", &input);
				if(List_isIndexOK(_this->list, input))
				{
					printf("%d��° ���� %d�� �����Ǿ����ϴ�.\n",input ,List_deleteKth (_this->list, input));
				}
				else
				{
					printf("�ùٸ��� ���� index �Դϴ�\n");
				}
			}
		}
		
		action =App_inputAction(_this) ;
	}

	List_free (_this->list);
	
} // End of while (action)

void App_outputStartingMessage(App * _this)
{
	printf ("%s", _this->startingMsg) ;
}

void App_outputEndingMessage (App * _this)
{
	printf ("\n%s\n", _this->endingMsg) ;
}

char App_inputAction (App * _this)
{
	printf("���ϴ� ������ ���� ���ڸ� �Է��ϼ��� : ");
	_this->input=getch();
	
	return _this->input;
}
void App_showAll (App * _this)
{
	Element e ;
	Iterator * iter ;
	
	iter = Iterator_new (_this->list) ;
	Iterator_begin(iter) ;

	while ( ! Iterator_endOfList(iter) ) 
	{
		e = Iterator_currentElement(iter) ;
		printf("%d ",e);
		Iterator_next(iter) ;
	}
	
	Iterator_free(iter) ;
}

void App_free (App * _this)
{
	free(_this->list);
	free(_this);
}