#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "App.h"

#define MSG_Starting "<List의 구현: Sorted Array>"
#define MSG_Ending "<프로그램을 종료합니다>"
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
	
	printf("\n'/. : 정수삽입, ! : 원소출력, + : 최대값삭제, ? : 임의삭제, # : 원소갯수보기, - : 최소값삭제, ~ : 리스트초기화, ESC : 종료\n");
	action =inputAction() ;
	while (action != Esc ) 
	{
		if ( action == ACTION_Insert ) 
		{
			printf("\n삽입할 숫자를 입력하세요 : ");
			scanf("%d", &input);
			if(this->list->doesExist(input))
			{
				printf("이미 존재하는 숫자입니다!\n");
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
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n최대값 %d가 삭제되었습니다.\n", this->list->deleteMax ());
			}
		}
		else if ( action == ACTION_ShowAll ) 
		{
			if(this->list->isEmpty ())
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n리스트의 원소를 출력합니다 : ");
				showAll();
				printf("\n");
			}
		}
		else if( action == ACTION_DeleteMin)
		{
			if(this->list->isEmpty ())
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n최소값 %d가 삭제되었습니다.\n", this->list->deleteMin ());
			}
		}

		else if(action == ACTION_Length)
		{
			printf("\n리스트의 원소의 갯수는 %d개 입니다.\n",this->list->Length());
		}
		else if(action == ACTION_Reset)
		{
			if(this->list->isEmpty ())
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				this->list->reset();
				printf("\n리스트를 비웠습니다.\n");
			}
		}
		else if(action == ACTION_deleteKth )
		{
			if(this->list->isEmpty ())
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n삭제할원소의 index를 입력하세요 : ");
				scanf("%d", &input);
				if(this->list->isIndexOK(input))
				{
					printf("%d번째 원소 %d가 삭제되었습니다.\n", input, this->list->deleteKth (input));
				}
				else
				{
					printf("올바르지 않은 index 입니다\n");
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
	printf("원하는 행위를 위한 문자를 입력하세요 : ");
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