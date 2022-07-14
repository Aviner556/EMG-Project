#ifndef _LED_
#define _LED_
#include "main.h"

typedef enum LED_STATE_
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
}LedState;

typedef struct _led
{
	LedState state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;
} Led;

void Led_init(Led* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Led_on(Led* led);
void Led_off(Led* led);
void Led_blink(Led* led, int period);
void Led_onTimerInterrupt(Led* led);
void Led_onPeriodicTask(Led* led);
void brightness(Led* led);

#endif
