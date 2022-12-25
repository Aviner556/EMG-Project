#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

struct DateTime
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
};

class Rtc
{
private:
	HAL_StatusTypeDef _HAL_STATUS_RTC;
	I2C_HandleTypeDef * _hi2c;
	uint8_t _devAddr;

public:
	Rtc()
	{
		_HAL_STATUS_RTC = HAL_OK;
		_hi2c = &hi2c1;
		_devAddr = 0xD0;
	}
	~Rtc(){}

	void rtcGetTime(DateTime * dateTime);
	void rtcSetTime(DateTime * dateTime);

};





#endif /* INC_RTC_H_ */
