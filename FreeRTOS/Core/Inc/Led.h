#ifndef _Led_
#define _Led_

#include "main.h"


typedef struct _Led
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	int ledDelay;
}Led;

void Led_init(Led * led,GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin);

#endif
