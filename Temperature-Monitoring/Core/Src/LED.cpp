#include "LED.h"
#include "main.h"


void LED::ledOn()
{
	if(_state == STATE_LED_ON){
		return;
	}
	_state = STATE_LED_ON;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}


void LED::ledOff()
{
	if(_state == STATE_LED_OFF){
		return;
	}
	this->_state = STATE_LED_OFF;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}


//replacing "onTimerIntterupt"
void LED::timerFunc()
{
	if(_state == STATE_LED_BLINK){
		HAL_GPIO_TogglePin(_port, _pin);
	}
}
