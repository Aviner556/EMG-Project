/*
 * ADC-Potentiometer.h
 *
 *  Created on: 11 בדצמ׳ 2022
 *      Author: Aviner
 */

#ifndef INC_ADC_POTENTIOMETER_H_
#define INC_ADC_POTENTIOMETER_H_

#include "ADC.h"

extern ADC_HandleTypeDef hadc1;


class AdcPotentiometer : public ADC
{
private:
	ADC_HandleTypeDef * _hadc;
	uint32_t _potentiometer;

public:
	AdcPotentiometer(){
		_hadc = &hadc1;
		_potentiometer = 0;
	}
	~AdcPotentiometer(){}

	ADC_HandleTypeDef * getADC(){
		return _hadc;
	}

	void setValue(){
		if(HAL_ADC_PollForConversion(_hadc, HAL_MAX_DELAY) == HAL_OK ){
			_potentiometer = HAL_ADC_GetValue(_hadc);
		}
	}

	uint32_t getValue(){
		return _potentiometer;
	}
};


#endif /* INC_ADC_POTENTIOMETER_H_ */
