#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

typedef struct DateTime_
	{
		int sec;
		int min;
		int hours;
		int weekDay;
		int day;
		int month;
		int year;
	}DateTime;

class Rtc
{
private:
	I2C_HandleTypeDef * _hi2c;
	uint8_t _devAddr;

public:
	Rtc(){
		_hi2c = &hi2c1;
		_devAddr = 0xD0;
	}
	~Rtc(){}

	void rtcGetTime(DateTime * dateTime);
	void rtcSetTime(DateTime * dateTime);

};





#endif /* INC_RTC_H_ */
