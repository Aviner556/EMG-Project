#ifndef _LED_
#define _LED_
#include "main.h"

typedef enum LED_STATE_
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
}LED_STATE;

typedef struct _led
{
	LED_STATE state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;
} LED;

void ledInit(LED* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void ledOn(LED* led);
void ledOff(LED* led);
void ledBlink(LED* led, int period);
void ledOnTimerInterrupt(LED* led);
void ledOnPeriodicTask(LED* led);
void setBrightness(int brightness);

#endif
