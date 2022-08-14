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
