#include <stdio.h>
#include <stdlib.h>
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

char App_inputAction (App * _this);
void App_showAll (App * _this);

struct _App 
{
	List * list ;
	char * startingMsg ;
	char * endingMsg ;
	char input;
// 필요하면 여기를 적절하게 더 채우시오.
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
	
	printf("\n'/. : 정수삽입, ! : 원소출력, + : 최대값삭제, ? : 임의삭제, # : 원소갯수보기, - : 최소값삭제, ~ : 리스트초기화, ESC : 종료\n");
	action =App_inputAction(_this) ;
	while (action != Esc ) 
	{
		if ( action == ACTION_Insert ) 
		{
			printf("\n삽입할 숫자를 입력하세요 : ");
			scanf("%d", &input);
			if(List_doesExist (_this->list, input))
			{
				printf("이미 존재하는 숫자입니다!\n");
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
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n최대값 %d가 삭제되었습니다.\n", List_deleteMax (_this->list));
			}
		}
		else if ( action == ACTION_ShowAll ) 
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n리스트의 원소를 출력합니다 : ");
				App_showAll(_this);
				printf("\n");
			}
		}
		else if( action == ACTION_DeleteMin)
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n최소값 %d가 삭제되었습니다.\n", List_deleteMin (_this->list));
			}
		}

		else if(action == ACTION_Length)
		{
			printf("\n리스트의 원소의 갯수는 %d개 입니다.\n", List_length(_this->list));
		}
		else if(action == ACTION_Reset)
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				List_reset(_this->list);
				printf("\n리스트를 비웠습니다.\n");
			}
		}
		else if(action == ACTION_deleteKth )
		{
			if(List_isEmpty (_this->list))
			{
				printf("\n리스트가 비었습니다!\n");
			}
			else
			{
				printf("\n삭제할원소의 index를 입력하세요 : ");
				scanf("%d", &input);
				if(List_isIndexOK(_this->list, input))
				{
					printf("%d번째 원소 %d가 삭제되었습니다.\n",input ,List_deleteKth (_this->list, input));
				}
				else
				{
					printf("올바르지 않은 index 입니다\n");
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
	printf("원하는 행위를 위한 문자를 입력하세요 : ");
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