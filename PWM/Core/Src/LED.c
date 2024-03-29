#include "LED.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim4;

void ledInit(LED* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led ->state = STATE_LED_OFF;
	led ->counter = 0;
	led ->GPIOx = GPIOx;
	led ->GPIO_Pin = GPIO_Pin;
	led ->period = 0;
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

void ledBlink(LED* led, int period)
{
	led ->counter = 0;
	led ->state = STATE_LED_BLINK;
	led ->period = period;
}

void ledOnTimerInterrupt(LED* led)
{
	if(led ->state == STATE_LED_BLINK){
		led ->counter++;
		if(led ->counter >= led ->period){
			HAL_GPIO_TogglePin(led ->GPIOx, led ->GPIO_Pin);
			led ->counter = 0;
		}
	}
}

void ledOnPeriodicTask(LED* led)
{

}

void setBrightness(int brightness)
{
	if(brightness < 0 || brightness > 10){
		printf("wrong parameter\r\n");
		return;
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, brightness*10);
}
