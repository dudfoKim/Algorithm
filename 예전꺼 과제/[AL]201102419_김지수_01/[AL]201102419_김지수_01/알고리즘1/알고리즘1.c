#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NewObject(TypeName) (TypeName *)malloc(sizeof(TypeName))//�����Ҵ� ��������
#define NewVector(TypeName,Length) (TypeName *)malloc(sizeof(TypeName)*Length)//�����Ҵ� ��������
#define NONE -1//NONE�� ����
#define Esc 27//Esc ����
#define ListMAXLENGTH 5//ListMAXLENGTH ���� 

typedef enum{FALSE, TRUE} Bool;//c���� Bool����� ���� ����

typedef struct A{
	int maxLength;
	int length;
	int* body;
}List;//����ü list����  

int inputNumber();//���� �Է� �Լ�
List* List_new(int maxSize);//�������� ����Ʈ ����
void List_free(List* _this);//����Ʈ ��ü �Ұ�
void List_reset(List* _this);//����Ʈ ���
Bool List_isFull(List* _this);//����á���� ���� �Ǵ�
Bool List_isEmpty(List* _this);//������� ���� �Ǵ�
Bool List_insert(List* _this, int element);//���� ����
int List_delete(List* _this);//ó�� �� ����
int List_max(List* _this);//�ִ밪 ã��
int List_length(List* _this);//����Ʈ ���� ���
Bool List_isIndexOK(List* _this, int index);//index �Ǻ�
Bool List_doesExist(List* _this, int element);//�Է������� ���翩�� �Ǻ�
void List_makeBigger(List* _this);//2��ũ��� ���Ҵ�
int List_maxRecursively(List* _this, int from, int to);//�ִ밪 ã��

int main()
{
	int printindex;//���������������� index
	char key;
	List* alist;//����Ʈ ����
	int i=0;//���� �ݺ��� ���� i
	
	alist=List_new(ListMAXLENGTH);//����Ʈ ����
 
	while(i!=TRUE)//i�� TRUE�� �ɶ�����
	{
		printindex=0;//�ʱ�ȭ
		
		while(printindex<alist->length)//���� ���� �������� ��������
		{
			if(printindex==0)
			{
				printf("������� : ");
			}
			printf("%d ", alist->body[printindex++]);//���� �迭�������
		}
		
		printf("\nN : �����Է�, D : �Ǿտ��� ����, R : ����Ʈ ����, M : �ִ밪ã��, L : ����Ʈ���̺���, ESC : ����\ninsertKEY\n ");
		key=getch();//Ű�Է�
		
		if(key==Esc)//esc�� �Էµɰ�� ���� 
		{
			i=TRUE;//i�� TRUE�� 
		}
		else if(key==78)//N�� �Էµɰ�� 
		{
			List_insert(alist, inputNumber());//�����Է�
		}
		else if(key==68)//D�� �Էµɰ��
		{
			if(List_isEmpty(alist))//����Ʈ�� ����ٸ� 
			{
				printf("�����Ҽ� �����ϴ�.\n");//���� �Ұ��� �޽��� ���
			}
			else//����Ʈ�� �����ʾҴٸ� 
			{
				printf("�����ȼ��� %d �Դϴ�.\n", List_delete(alist));//�����ϰ� �����Ǿ��� �� ���
			}
		}
		else if(key==82)//R�� �Էµɰ�� 
		{
			List_reset(alist);//����Ʈ�� ����
		}
		else if(key==77)//�ִ밪 ã�� ���
		{
			if(List_isEmpty(alist))//����Ʈ�� ��������
			{
				printf("����Ʈ�� ������ϴ�.\n");//�޽��� ���
			}
			else//����Ʈ�� ���� �ʾ������
			{
				printf("�ִ밪�� %d �Դϴ�.\n",List_max(alist));//�ִ밪 ���
			}
		}
		else if(key==76)//L�� �Էµɰ��  
		{
			printf("���� ����Ʈ�� ���̴� %d �Դϴ�. \n", List_length(alist));//����Ʈ�� �������
		}
	}
	
	return 0;
}

int inputNumber()
{
	int inputnum;
	
	printf("�����Է� : "); 
	scanf("%d", &inputnum);//������ �Է¹���

	return inputnum;//�Է¹��� ���� ����
}
List* List_new(int maxSize)
{
	List* temp=NewObject(List);//���ο� ����Ʈ ��������
	int i=0;
	
	temp->maxLength=maxSize;//�ִ� ���̸� �ִ� ������� 
	temp->length=0;//�����ʱⰳ���� 0�� 
	temp->body=NewVector(int ,maxSize);//�迭 �����Ҵ�

	while(i<maxSize)
	{
		temp->body[i++]=0;//�迭�� �ʱ�ȭ
	}

	return temp;//������ ����Ʈ ��ȯ
}

Bool List_insert(List* _this, int element)
{
	if(List_doesExist(_this, element))//���ڰ� �̹� �����Ұ��
	{
		printf("�̹� �����ϴ� ���Դϴ�.\n");//�޽��� ���

		return FALSE;//FALSE ��ȯ
	}
	if(List_isFull(_this))//�迭�� ����á�����
	{
		List_makeBigger(_this);//2��ũ��� ���Ҵ�
	}

	_this->body[_this->length++]=element;//�Է¹����� �־���
}

Bool List_doesExist(List* _this, int element)
{
	int i=0;
	
	while((_this->length)>i)//������ ������ŭ �ݺ�
	{
		if((_this->body[i++])==element)//�ߺ��� �������
		{
			return TRUE;//TRUE��ȯ
		}
	}

	return FALSE;//�ߺ��� ������� FALSE ��ȯ
}
Bool List_isFull(List* _this)
{
	if(_this->length==_this->maxLength)//���� ���Ұ����� �ִ� ���Ұ����� �������
	{
		return TRUE;//TRUE ��ȯ
	}

	return FALSE;//���� FULL�� �ƴҰ�� FALSE ��ȯ
}
void List_makeBigger(List * _this)
{
	int* temp;
	int index1=0, index2=0;
	
	temp=NewVector(int, (_this->maxLength)*2);//2��¥�� temp�迭 �����Ҵ�
	
	while(index1<_this->maxLength*2)
	{
		temp[index1++]=0;//temp�迭 �ʱ�ȭ
	}
	
	while(index2<_this->length)
	{
		temp[index2]=_this->body[index2++];//���� ����Ʈ�� �迭���� temp�� �̵�
	}
	
	List_free (_this);//���� �迭�� ����

	_this->maxLength=_this->maxLength*2;//�ִ� ũ�⸦ �÷���
	_this->body=temp;//����Ʈ�� �迭�� 2��ũ���� temp�� ����
}

Bool List_isIndexOK (List * _this, int index)
{
	if(index>=0&&(_this->length>index))//�ε������� 0���� ũ�� ���� ���Ҽ����� ������� 
	{
		return TRUE;//TRUE��ȯ
	}

	return FALSE;//�ƴҰ�� FALSE ��ȯ
}
Bool List_isEmpty (List * list)
{
	if(list->length==0)//���Ұ����� 0�����
	{
		return TRUE;//TRUE ��ȯ
	}
	return FALSE;//FALSE ��ȯ
}

int List_delete (List * _this)
{
	int temp=_this->body[0];//temp�� �����ϱ��� �� ����
	int i=0;

	while(i<_this->length)//���Ҽ����� �������� �ݺ�
	{
		(_this->body[i])=(_this->body[i+1]);//�����͸� ��ĭ���Ű���
		_this->body[i+1]=0;//������ĭ�� 0����
		i++;
	}
	
	_this->length--;//���Ҹ� �Ѱ� ���������Ƿ� ����
	
	return temp;//�����Ȱ� ��ȯ
}

void List_reset (List * _this)
{
	_this->length=0;//����Ʈ�� ���Ҽ��� 0���� ����
}

int List_max (List * _this)
{
	List_maxRecursively(_this, 0, _this->length-1);//����Լ��� maxRecursively�ҷ���
}

int List_maxRecursively(List * _this, int from, int to)
{
	int mid, leftMax, rightMax;

	if((to-from)<=1)//�����Ѱ� ������ �Ѱ��� ���� ���̻� �ɰ��� �������
	{
		leftMax=_this->body[from];//���ʿ��Ҹ� �����ִ밪����
		rightMax=_this->body[to];//�����ʿ��Ҹ� �������ִ밪����
	}
	else//���� �ɰ��� �������
	{
		leftMax=0;
		rightMax=0;
		mid = (from+to)/2;//�ɰ�
		leftMax = List_maxRecursively(_this, from, mid);//����Լ�ȣ��
		rightMax = List_maxRecursively(_this, mid+1,to);//����Լ�ȣ��
	}
	
	return ((leftMax >= rightMax)? leftMax : rightMax);//������ �����߿� ū�� ��ȯ
}
int List_length (List * list)
{
	return list->length;//����Ʈ ���� ��ȯ
}

void List_free (List * list)
{
	free(list->body);//����Ʈ�� �迭�� free
}