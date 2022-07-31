#include "Clock.h"
#include "MainTimerIT.h"
#include "main.h"

void Clock_init(Clock * clock)
{
	clock->tik = 0;
	clock->seconds = 0;
	clock->minutes = 0;
	clock->hours = 0;
	clock->days = 0;
	MainTimerIT_registerCallback(Clock_workingTime, clock);
}

void Clock_workingTime(void * obj)
{
	Clock * clock = (Clock *)obj;
	clock->tik = HAL_GetTick();
	clock->seconds = clock->tik/1000;
	clock->minutes = clock->tik/60000;
	clock->hours = clock->tik/3600000;
	clock->days = clock->tik/86400000;
}

void Clock_showTime(Clock * clock)
{
	Clock_workingTime(clock);
	printf("%d:%d:%d:%d\r\n\n",clock->days,clock->hours%24,clock->minutes%60,clock->seconds%60);
}
