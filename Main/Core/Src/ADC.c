#include "ADC.h"
#include "main.h"

extern ADC_HandleTypeDef hadc2;

void adcInit(ADC* adc)
{
	adc->value = 0;
	adc->count = 0;
}

//void adcPrint(ADC* adc)
//{
//	if(adc == &hadc2){
//		adc->count++;
//		if(adc->count >= 1000){
//			printf("light sensor = %lu\r\n",adc->value);
//			adc->count = 0;
//		}
//	}
//}
