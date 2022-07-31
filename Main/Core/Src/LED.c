#include "Led.h"
#include "MainTimerIT.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim4;

void Led_init(Led * led,GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin)
{
	led->state = STATE_LED_OFF;
	led->counter = 0;
	led->gpioPort = GPIOx;
	led->gpioPin = GPIO_Pin;
	led->maxPeriod = 0;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}

void Led_on(Led * led)
{
	led ->state = STATE_LED_ON;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);
	MainTimerIT_registerCallbackRemove(Led_onTimerInterrupt, led);
}

void Led_off(Led * led)
{
	led ->state = STATE_LED_OFF;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
	MainTimerIT_registerCallbackRemove(Led_onTimerInterrupt, led);
}

void Led_blink(Led * led, int maxPeriod)
{
	led ->counter = 0;
	led ->state = STATE_LED_BLINK;
	led ->maxPeriod = maxPeriod;
	MainTimerIT_registerCallback(Led_onTimerInterrupt, led);
}

void Led_onTimerInterrupt(void * obj)
{
	Led * led = (Led *)obj;
	if(led ->state == STATE_LED_BLINK){
		led ->counter++;
		if(led ->counter >= led ->maxPeriod){
			HAL_GPIO_TogglePin(led->gpioPort, led->gpioPin);
			led ->counter = 0;
		}
	}
}

void Led_brightness(int bright)
{
	if(bright > 10 || bright < 0){
		printf("invalid command\r\n");
		return;
	}
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, bright);
}

void Led_onPeriodicTask(Led* led)
{

}

//int cnt = 0;
//void brightness(LED* led)
//{
//
//}
