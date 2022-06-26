#include "LED.h"

void ledInit(LED* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led ->state = STATE_LED_OFF;
	led ->counter = 0;
	led ->GPIOx = GPIOx;
	led ->GPIO_Pin = GPIO_Pin;
	led ->maxPeriod = 0;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 0);
}

void ledOn(LED* led)
{
	led ->state = STATE_LED_ON;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 1);
}

void ledOff(LED* led)
{
	led ->state = STATE_LED_OFF;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 0);
}

void ledBlink(LED* led, int maxPeriod)
{
	led ->counter = 0;
	led ->state = STATE_LED_BLINK;
	led ->maxPeriod = maxPeriod;
}

void ledOnTimerInterrupt(LED* led)
{
	if(led ->state == STATE_LED_BLINK){
		led ->counter++;
		if(led ->counter >= led ->maxPeriod){
			HAL_GPIO_TogglePin(led ->GPIOx, led ->GPIO_Pin);
			led ->counter = 0;
		}
	}
}

void ledOnPeriodicTask(LED* led)
{

}

//int cnt = 0;
//void brightness(LED* led)
//{
//
//}
