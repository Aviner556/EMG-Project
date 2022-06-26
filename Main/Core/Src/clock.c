#include "clock.h"

void clockInit(CLOCK* clock)
{
	clock ->tik = 0;
	clock ->seconds = 0;
	clock ->minutes = 0;
	clock ->hours = 0;
	clock ->days = 0;
}

void workingTime(CLOCK* clock)
{
	clock->tik = HAL_GetTick();
	clock->seconds = clock->tik/1000;
	clock->minutes = clock->tik/60000;
	clock->hours = clock->tik/3600000;
	clock->days = clock->tik/86400000;
}


void showTime(CLOCK* clock)
{
	workingTime(clock);
	printf("%d:%d:%d:%d\n\r",clock->days,clock->hours%24,clock->minutes%60,clock->seconds%60);
}
