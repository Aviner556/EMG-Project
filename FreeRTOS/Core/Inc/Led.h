#ifndef _Led_
#define _Led_

#include "main.h"

typedef struct _QUEUE_MSG
{
	uint16_t bright;
	uint16_t delay;
}QUEUE_MSG;

typedef struct _Led
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	int ledDelay;
	int ledBright;
}Led;

void Led_init(Led * led, GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin);
void Led_brightness(int bright);

#endif
