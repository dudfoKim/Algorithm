#include <stdio.h>
#include <Windows.h> // 속도 측정을 위한 Header
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
	QueryPerformanceFrequency( &(_this->frequency) ) ; // 주파수( 1초당 증가되는 카운트 수)를 구한다.
	
	return _this ;
}
void Timer_free (Timer * _this)
{
	free (_this) ;
}
void Timer_start (Timer * _this)
{
	QueryPerformanceCounter( &(_this ->startCounter) ) ; // 실행 전 카운트를 구한다.
}
void Timer_stop (Timer * _this)
{
	QueryPerformanceCounter( &(_this ->stopCounter) ) ; // 실행 후 카운트를 구한다.
}
double Timer_duration (Timer * _this)
{
	return ( (double) (_this ->stopCounter.QuadPart - _this ->startCounter.QuadPart )*1000000.0 / (double) _this ->frequency.QuadPart ) ;
// 실행 시간을 나노 초로 변환한다.
}