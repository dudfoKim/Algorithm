#include "Global.h"

typedef struct _Timer Timer;

Timer * Timer_new ();//타이머 생성
void Timer_free (Timer * _this);//타이머 소멸
void Timer_start (Timer * _this);//타이머 작동 시작
void Timer_stop (Timer * _this);//타이머 작동 중지
double Timer_duration (Timer * _this);//타이머 작동 시작부터 중지까지의 시간 (단위: nano second)
