#include "LED.h"

void Led_init(Led* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led ->state = STATE_LED_OFF;
	led ->counter = 0;
	led ->GPIOx = GPIOx;
	led ->GPIO_Pin = GPIO_Pin;
	led ->period = 0;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 0);
}

void Led_on(Led* led)
{
	led ->state = STATE_LED_ON;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 1);
}

void Led_off(Led* led)
{
	led ->state = STATE_LED_OFF;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 0);
}

void Led_blink(Led* led, int period)
{
	led ->counter = 0;
	led ->state = STATE_LED_BLINK;
	led ->period = period;
}

void Led_onTimerInterrupt(Led* led)
{
	if(led ->state == STATE_LED_BLINK){
		led ->counter++;
		if(led ->counter >= led ->period){
			HAL_GPIO_TogglePin(led ->GPIOx, led ->GPIO_Pin);
			led ->counter = 0;
		}
	}
}

void Led_onPeriodicTask(Led* led)
{

}

//int cnt = 0;
//void brightness(LED* led)
//{
//
//}
