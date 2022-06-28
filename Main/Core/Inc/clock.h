#ifndef _clock_
#define _clock_

#include <stdio.h>

typedef struct _CLOCK
{
	uint32_t tik;
	int seconds;
	int minutes;
	int hours;
	int days;
}CLOCK;

void clockInit(CLOCK* clock);
void workingTime(CLOCK* clock);
void showTime(CLOCK* clock);


#endif
