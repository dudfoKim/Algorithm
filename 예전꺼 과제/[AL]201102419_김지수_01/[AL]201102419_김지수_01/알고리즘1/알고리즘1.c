#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NewObject(TypeName) (TypeName *)malloc(sizeof(TypeName))//동적할당 사전정의
#define NewVector(TypeName,Length) (TypeName *)malloc(sizeof(TypeName)*Length)//동적할당 사전정의
#define NONE -1//NONE값 정의
#define Esc 27//Esc 정의
#define ListMAXLENGTH 5//ListMAXLENGTH 정의 

typedef enum{FALSE, TRUE} Bool;//c에서 Bool사용을 위한 정의

typedef struct A{
	int maxLength;
	int length;
	int* body;
}List;//구조체 list선언  

int inputNumber();//정수 입력 함수
List* List_new(int maxSize);//동적으로 리스트 생성
void List_free(List* _this);//리스트 객체 소거
void List_reset(List* _this);//리스트 비움
Bool List_isFull(List* _this);//가득찼는지 여부 판단
Bool List_isEmpty(List* _this);//비었는지 여부 판단
Bool List_insert(List* _this, int element);//정수 삽입
int List_delete(List* _this);//처음 값 삭제
int List_max(List* _this);//최대값 찾기
int List_length(List* _this);//리스트 길이 출력
Bool List_isIndexOK(List* _this, int index);//index 판별
Bool List_doesExist(List* _this, int element);//입력정수의 존재여부 판별
void List_makeBigger(List* _this);//2배크기로 재할당
int List_maxRecursively(List* _this, int from, int to);//최대값 찾기

int main()
{
	int printindex;//현재상태출력을위한 index
	char key;
	List* alist;//리스트 선언
	int i=0;//메인 반복을 위한 i
	
	alist=List_new(ListMAXLENGTH);//리스트 생성
 
	while(i!=TRUE)//i가 TRUE가 될때까지
	{
		printindex=0;//초기화
		
		while(printindex<alist->length)//현재 원소 갯수보다 작은동안
		{
			if(printindex==0)
			{
				printf("현재상태 : ");
			}
			printf("%d ", alist->body[printindex++]);//현재 배열상태출력
		}
		
		printf("\nN : 정수입력, D : 맨앞원소 삭제, R : 리스트 비우기, M : 최대값찾기, L : 리스트길이보기, ESC : 종료\ninsertKEY\n ");
		key=getch();//키입력
		
		if(key==Esc)//esc가 입력될경우 종료 
		{
			i=TRUE;//i를 TRUE로 
		}
		else if(key==78)//N이 입력될경우 
		{
			List_insert(alist, inputNumber());//정수입력
		}
		else if(key==68)//D가 입력될경우
		{
			if(List_isEmpty(alist))//리스트가 비었다면 
			{
				printf("삭제할수 없습니다.\n");//삭제 불가능 메시지 출력
			}
			else//리스트가 비지않았다면 
			{
				printf("삭제된수는 %d 입니다.\n", List_delete(alist));//삭제하고 삭제되어진 수 출력
			}
		}
		else if(key==82)//R이 입력될경우 
		{
			List_reset(alist);//리스트를 리셋
		}
		else if(key==77)//최대값 찾아 출력
		{
			if(List_isEmpty(alist))//리스트가 비었을경우
			{
				printf("리스트가 비었습니다.\n");//메시지 출력
			}
			else//리스트가 비지 않았을경우
			{
				printf("최대값은 %d 입니다.\n",List_max(alist));//최대값 출력
			}
		}
		else if(key==76)//L이 입력될경우  
		{
			printf("현재 리스트의 길이는 %d 입니다. \n", List_length(alist));//리스트의 길이출력
		}
	}
	
	return 0;
}

int inputNumber()
{
	int inputnum;
	
	printf("정수입력 : "); 
	scanf("%d", &inputnum);//정수를 입력받음

	return inputnum;//입력받은 정수 리턴
}
List* List_new(int maxSize)
{
	List* temp=NewObject(List);//새로운 리스트 동적선언
	int i=0;
	
	temp->maxLength=maxSize;//최대 길이를 최대 사이즈로 
	temp->length=0;//원소초기개수는 0개 
	temp->body=NewVector(int ,maxSize);//배열 동적할당

	while(i<maxSize)
	{
		temp->body[i++]=0;//배열값 초기화
	}

	return temp;//생성된 리스트 반환
}

Bool List_insert(List* _this, int element)
{
	if(List_doesExist(_this, element))//숫자가 이미 존재할경우
	{
		printf("이미 존재하는 수입니다.\n");//메시지 출력

		return FALSE;//FALSE 반환
	}
	if(List_isFull(_this))//배열이 가득찼을경우
	{
		List_makeBigger(_this);//2배크기로 재할당
	}

	_this->body[_this->length++]=element;//입력받은값 넣어줌
}

Bool List_doesExist(List* _this, int element)
{
	int i=0;
	
	while((_this->length)>i)//원소의 개수만큼 반복
	{
		if((_this->body[i++])==element)//중복이 있을경우
		{
			return TRUE;//TRUE반환
		}
	}

	return FALSE;//중복이 없을경우 FALSE 반환
}
Bool List_isFull(List* _this)
{
	if(_this->length==_this->maxLength)//현재 원소갯수가 최대 원소갯수와 같을경우
	{
		return TRUE;//TRUE 반환
	}

	return FALSE;//현재 FULL이 아닐경우 FALSE 반환
}
void List_makeBigger(List * _this)
{
	int* temp;
	int index1=0, index2=0;
	
	temp=NewVector(int, (_this->maxLength)*2);//2배짜리 temp배열 동적할당
	
	while(index1<_this->maxLength*2)
	{
		temp[index1++]=0;//temp배열 초기화
	}
	
	while(index2<_this->length)
	{
		temp[index2]=_this->body[index2++];//기존 리스트의 배열값을 temp로 이동
	}
	
	List_free (_this);//기존 배열은 삭제

	_this->maxLength=_this->maxLength*2;//최대 크기를 늘려줌
	_this->body=temp;//리스트의 배열을 2배크기의 temp로 해줌
}

Bool List_isIndexOK (List * _this, int index)
{
	if(index>=0&&(_this->length>index))//인덱스값이 0보다 크고 현재 원소수보다 작을경우 
	{
		return TRUE;//TRUE반환
	}

	return FALSE;//아닐경우 FALSE 반환
}
Bool List_isEmpty (List * list)
{
	if(list->length==0)//원소갯수가 0개라면
	{
		return TRUE;//TRUE 반환
	}
	return FALSE;//FALSE 반환
}

int List_delete (List * _this)
{
	int temp=_this->body[0];//temp에 삭제하기전 값 저장
	int i=0;

	while(i<_this->length)//원소수보다 작을동안 반복
	{
		(_this->body[i])=(_this->body[i+1]);//데이터를 한칸씩옮겨줌
		_this->body[i+1]=0;//마지막칸은 0으로
		i++;
	}
	
	_this->length--;//원소를 한개 삭제했으므로 감소
	
	return temp;//삭제된값 반환
}

void List_reset (List * _this)
{
	_this->length=0;//리스트의 원소수를 0개로 해줌
}

int List_max (List * _this)
{
	List_maxRecursively(_this, 0, _this->length-1);//재귀함수인 maxRecursively불러줌
}

int List_maxRecursively(List * _this, int from, int to)
{
	int mid, leftMax, rightMax;

	if((to-from)<=1)//왼쪽한개 오른쪽 한개가 남아 더이상 쪼갤수 없을경우
	{
		leftMax=_this->body[from];//왼쪽원소를 왼쪽최대값으로
		rightMax=_this->body[to];//오른쪽원소를 오른쪽최대값으로
	}
	else//아직 쪼갤수 있을경우
	{
		leftMax=0;
		rightMax=0;
		mid = (from+to)/2;//쪼갬
		leftMax = List_maxRecursively(_this, from, mid);//재귀함수호출
		rightMax = List_maxRecursively(_this, mid+1,to);//재귀함수호출
	}
	
	return ((leftMax >= rightMax)? leftMax : rightMax);//오른쪽 왼쪽중에 큰값 반환
}
int List_length (List * list)
{
	return list->length;//리스트 길이 반환
}

void List_free (List * list)
{
	free(list->body);//리스트의 배열을 free
}