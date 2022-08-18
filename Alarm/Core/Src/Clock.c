#include "Clock.h"
#include <stdio.h>

DateTime T;

int Clock_getTime(uint8_t* readBuff)
{
	T.second1 = readBuff[0]&15;
	T.second10 = readBuff[0]>>4;
	T.minute1 = readBuff[1]&15;
	T.minutes10 = readBuff[1]>>4;
	T.hour1 = readBuff[2]&15;
	T.hours10 = readBuff[2]>>4&3;

	int time = T.second1 + (T.second10 * 10) +
			  (T.minute1 + (T.minutes10 * 10)) * 60 +
			  (T.hour1 + (T.hours10 * 10)) * 3600;
	return time;
}

void Clock_printTime(uint8_t* readBuff)
{
	T.second1 = readBuff[0]&15;
	T.second10 = readBuff[0]>>4;
	T.minute1 = readBuff[1]&15;
	T.minutes10 = readBuff[1]>>4;
	T.hour1 = readBuff[2]&15;
	T.hours10 = readBuff[2]>>4&3;
	T.weekDay = readBuff[3]&7;
	T.day1 = readBuff[4]&15;
	T.days10 = readBuff[4]>>4&3;
	T.month1 = readBuff[5]&15;
	T.months10 = readBuff[5]>>4&1;
	T.year1 = readBuff[6]&15;
	T.years10 = readBuff[6]>>4;

	printf("%d%d/%d%d/20%d%d : DAY-%d : %d%d:%d%d:%d%d\r\n",T.days10,T.day1,T.months10,T.month1,T.years10,T.year1,T.weekDay,T.hours10,T.hour1,T.minutes10,T.minute1,T.second10,T.second1);
}
