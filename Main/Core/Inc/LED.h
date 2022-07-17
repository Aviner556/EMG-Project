#ifndef _Led_
#define _Led_

#include "main.h"

typedef enum LedState_
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
}LedState;

typedef struct _Led
{
	LedState state;
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	int counter;
	int maxPeriod;
}Led;

void Led_init(Led * led,GPIO_TypeDef * gpioPort, uint16_t gpioPin);
void Led_on(Led * led);
void Led_off(Led * led);
void Led_blink(Led * led, int period);
void Led_onTimerInterrupt(Led * led);
void Led_onPeriodicTask(Led * led);
void Led_brightness(int bright);

#endif
