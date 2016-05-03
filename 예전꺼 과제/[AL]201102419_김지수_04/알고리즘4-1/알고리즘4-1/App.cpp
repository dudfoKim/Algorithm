#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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

char * App::msg_Starting = App_MSG_Starting ;
char * App::msg_Ending = App_MSG_Ending ;

App::App ()
{
	
	this->list = new List() ;
	this->msg_Starting = MSG_Starting ;
	this->msg_Ending = MSG_Ending ;
}

void App::run ()
{
	char action;
	int input;
	
	printf("\n'/. : ��������, ! : �������, + : �ִ밪����, ? : ���ǻ���, # : ���Ұ�������, - : �ּҰ�����, ~ : ����Ʈ�ʱ�ȭ, ESC : ����\n");
	action =inputAction() ;
	while (action != Esc ) 
	{
		if ( action == ACTION_Insert ) 
		{
			printf("\n������ ���ڸ� �Է��ϼ��� : ");
			scanf("%d", &input);
			if(this->list->doesExist(input))
			{
				printf("�̹� �����ϴ� �����Դϴ�!\n");
			}
			else
			{
				this->list->insert (input);
			}
		}
		else if ( action == ACTION_DeleteMax ) 
		{
			if(this->list->isEmpty ())
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n�ִ밪 %d�� �����Ǿ����ϴ�.\n", this->list->deleteMax ());
			}
		}
		else if ( action == ACTION_ShowAll ) 
		{
			if(this->list->isEmpty ())
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n����Ʈ�� ���Ҹ� ����մϴ� : ");
				showAll();
				printf("\n");
			}
		}
		else if( action == ACTION_DeleteMin)
		{
			if(this->list->isEmpty ())
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n�ּҰ� %d�� �����Ǿ����ϴ�.\n", this->list->deleteMin ());
			}
		}

		else if(action == ACTION_Length)
		{
			printf("\n����Ʈ�� ������ ������ %d�� �Դϴ�.\n",this->list->Length());
		}
		else if(action == ACTION_Reset)
		{
			if(this->list->isEmpty ())
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				this->list->reset();
				printf("\n����Ʈ�� ������ϴ�.\n");
			}
		}
		else if(action == ACTION_deleteKth )
		{
			if(this->list->isEmpty ())
			{
				printf("\n����Ʈ�� ������ϴ�!\n");
			}
			else
			{
				printf("\n�����ҿ����� index�� �Է��ϼ��� : ");
				scanf("%d", &input);
				if(this->list->isIndexOK(input))
				{
					printf("%d��° ���� %d�� �����Ǿ����ϴ�.\n", input, this->list->deleteKth (input));
				}
				else
				{
					printf("�ùٸ��� ���� index �Դϴ�\n");
				}
			}
		}
		
		action =inputAction() ;
	}
} // End of while (action)

void App::outputMsg_Starting ()
{
	printf ("%s", this->msg_Starting) ;
}

void App::outputMsg_Ending ()
{
	printf ("\n%s\n", this->msg_Ending) ;
}

char App::inputAction ()
{
	printf("���ϴ� ������ ���� ���ڸ� �Է��ϼ��� : ");
	this->input=getch();
	
	return this->input;
}
void App::showAll ()
{
	Element e ;
	Iter * iter=new Iter(this->list);
	
	iter->begin () ;

	while ( !iter->endOfList() ) 
	{
		e = iter->currentElement() ;
		printf("%d ",e);
		iter->next ();
	}
}