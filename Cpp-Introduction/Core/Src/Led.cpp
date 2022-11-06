#include <Led.h>

extern LED blueLed;

void LED::ledOn()
{
	/*
	if(blueLed._state == STATE_LED_ON){
		return;
	}
	*/
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}

void LED::ledOff()
{
	/*
	if(blueLed._state == STATE_LED_OFF){
		return;
	}
	*/
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}

void LED::ledBlink()
{
	/*
	if(blueLed._state == STATE_LED_BLINK){
		return;
	}
	*/
	HAL_GPIO_TogglePin(_port, _pin);
	HAL_Delay(500);
}

/*
void LED::ledChangeState()
{
	if(blueLed._state == STATE_LED_OFF){
		blueLed._state = STATE_LED_ON;
	}
	else if(blueLed._state == STATE_LED_ON){
		blueLed._state = STATE_LED_BLINK;
	}
	else if(blueLed._state == STATE_LED_BLINK){
		blueLed._state = STATE_LED_OFF;
	}
}
*/

LedState LED::ledGetState()
{
	return blueLed._state;
}

/*
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
*/
