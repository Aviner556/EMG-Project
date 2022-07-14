#ifndef _Clock_
#define _Clock_

#include <stdio.h>

typedef struct _Clock
{
	uint32_t tik;
	int seconds;
	int minutes;
	int hours;
	int days;
}Clock;

void Clock_init(Clock * clock);
void Clock_workingTime(Clock * clock);
void Clock_showTime(Clock * clock);


#endif
