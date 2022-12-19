/*
 * ADC-LightSensor.h
 *
 *  Created on: 11 בדצמ׳ 2022
 *      Author: Aviner
 */

#ifndef INC_ADC_LIGHTSENSOR_H_
#define INC_ADC_LIGHTSENSOR_H_


#include "ADC.h"
#include "main.h"

extern ADC_HandleTypeDef hadc2;


class AdcLightSensor : public ADC
{
private:
	ADC_HandleTypeDef * _hadc;
	uint32_t _lightSensor;

public:
	AdcLightSensor(){
		_hadc = &hadc2;
		_lightSensor = 0;
	}
	~AdcLightSensor(){}

	ADC_HandleTypeDef * getADC(){
		return _hadc;
	}

	void setValue(){
		if(HAL_ADC_PollForConversion(_hadc, HAL_MAX_DELAY) == HAL_OK ){
			_lightSensor = HAL_ADC_GetValue(_hadc);
		}
	}

	uint32_t getValue(){
		return _lightSensor;
	}
};


#endif /* INC_ADC_LIGHTSENSOR_H_ */
