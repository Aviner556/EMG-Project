#ifndef _LED_
#define _LED_
#include "main.h"


typedef struct _led
{
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;
} Led;


void Led_init(Led* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#endif
