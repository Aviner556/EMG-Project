#include "Led-Gpio.h"
#include "main.h"




void LedGpio::ledOn()
{
	if(_state == STATE_LED_ON){
		return;
	}
	_state = STATE_LED_ON;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}


void LedGpio::ledOff()
{
	if(_state == STATE_LED_OFF){
		return;
	}
	this->_state = STATE_LED_OFF;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}


void LedGpio::ledBlink(int maxPeriod)
{
	_maxPeriod = maxPeriod;
	if(_state == STATE_LED_BLINK){
		return;
	}
	_state = STATE_LED_BLINK;
	MainTimerIT_registerCallback(this);
}


//replacing "onTimerIntterupt"
void LedGpio::timerFunc()
{
	if(_state == STATE_LED_BLINK){
		_counter++;
		if(_counter >= _maxPeriod){
			HAL_GPIO_TogglePin(_port, _pin);
			_counter = 0;
		}
	}
}
