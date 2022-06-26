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
	clock ->tik = HAL_GetTick();
	clock ->seconds = clock ->tik/1000;
	clock ->minutes = clock ->tik/60000;
	clock ->hours = clock ->tik/360000;
	clock ->days = clock ->tik/8640000;
}
