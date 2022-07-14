#ifndef _Adc_
#define _Adc_

#include <stdio.h>

typedef struct _Adc
{
	uint32_t value;
	int count;
}Adc;

void Adc_Init(Adc * adc);
void Adc_Print(Adc * adc);

#endif
