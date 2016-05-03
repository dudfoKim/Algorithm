#include <stdio.h>
#include <Windows.h> // �ӵ� ������ ���� Header
#include "Timer.h"


struct _Timer
{
	LARGE_INTEGER frequency ;
	LARGE_INTEGER startCounter ;
	LARGE_INTEGER stopCounter ;
};

Timer * Timer_new (void)
{
	Timer * _this = NewObject(Timer) ;
	QueryPerformanceFrequency( &(_this->frequency) ) ; // ���ļ�( 1�ʴ� �����Ǵ� ī��Ʈ ��)�� ���Ѵ�.
	
	return _this ;
}
void Timer_free (Timer * _this)
{
	free (_this) ;
}
void Timer_start (Timer * _this)
{
	QueryPerformanceCounter( &(_this ->startCounter) ) ; // ���� �� ī��Ʈ�� ���Ѵ�.
}
void Timer_stop (Timer * _this)
{
	QueryPerformanceCounter( &(_this ->stopCounter) ) ; // ���� �� ī��Ʈ�� ���Ѵ�.
}
double Timer_duration (Timer * _this)
{
	return ( (double) (_this ->stopCounter.QuadPart - _this ->startCounter.QuadPart )*1000000.0 / (double) _this ->frequency.QuadPart ) ;
// ���� �ð��� ���� �ʷ� ��ȯ�Ѵ�.
}