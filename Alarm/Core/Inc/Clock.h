#ifndef _Clock_
#define _Clock_

#include <stdio.h>

typedef struct DateDime_
{
	int second1;
	int second10;
	int minute1;
	int minutes10;
	int hour1;
	int hours10;
	int weekDay;
	int day1;
	int days10;
	int month1;
	int months10;
	int year1;
	int years10;
}DateTime;

int Clock_getTime(uint8_t* readBuff);


#endif
