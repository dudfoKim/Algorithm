#include "Global.h"

typedef struct _Timer Timer;

Timer * Timer_new ();//Ÿ�̸� ����
void Timer_free (Timer * _this);//Ÿ�̸� �Ҹ�
void Timer_start (Timer * _this);//Ÿ�̸� �۵� ����
void Timer_stop (Timer * _this);//Ÿ�̸� �۵� ����
double Timer_duration (Timer * _this);//Ÿ�̸� �۵� ���ۺ��� ���������� �ð� (����: nano second)
