/*
 * ADC.h
 *
 *  Created on: 11 בדצמ׳ 2022
 *      Author: Aviner
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

class ADC
{
private:
	ADC_HandleTypeDef _hadc;

public:
	ADC(){};
	~ADC(){}

	virtual ADC_HandleTypeDef * getADC() = 0;
	virtual void setValue() = 0;
	virtual uint32_t getValue() = 0;
};

void AdcInterrupt(ADC_HandleTypeDef* hadc, ADC * adcP, ADC * adcL)
{
	if(hadc == adcP->getADC()){
		if(HAL_ADC_PollForConversion(adcP->getADC(), HAL_MAX_DELAY) == HAL_OK ){
			adcP->setValue();
			HAL_ADC_Stop_IT(adcP->getADC());
		}
	}
	if(hadc == adcL->getADC()){
		if(HAL_ADC_PollForConversion(adcL->getADC(), HAL_MAX_DELAY) == HAL_OK ){
			adcL->setValue();
			HAL_ADC_Stop_IT(adcL->getADC());
		}
	}
}


#endif /* INC_ADC_H_ */
