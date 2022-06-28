#ifndef _ADC_
#define _ADC_

#include <stdio.h>

typedef struct _ADC
{
	uint32_t value;
	int count;
}ADC;

void adcInit(ADC* adc);
void adcPrint(ADC* adc);

#endif
