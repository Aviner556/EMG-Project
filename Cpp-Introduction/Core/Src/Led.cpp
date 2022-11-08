#include "Led.h"
#include "main.h"
#include "stdio.h"

extern LED blueLed;
extern TIM_HandleTypeDef htim2;

void LED::ledOn()
{
	if(blueLed._state == STATE_LED_ON){
		return;
	}
	this->_state = STATE_LED_ON;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}


void LED::ledOff()
{
	if(blueLed._state == STATE_LED_OFF){
		return;
	}
	this->_state = STATE_LED_OFF;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}


void LED::ledBlink(int maxPeriod)
{
	_maxPeriod = maxPeriod;
	if(blueLed._state == STATE_LED_BLINK){
		return;
	}
	this->_state = STATE_LED_BLINK;
	MainTimerIT_registerCallback(this);
}


//replacing "onTimerIntterupt"
void LED::timerFunc()
{
	if(_state == STATE_LED_BLINK){
		_counter++;
		if(_counter >= _maxPeriod){
			HAL_GPIO_TogglePin(_port, _pin);
			_counter = 0;
		}
	}
}


void LED::ledBrightness(int bright)
{
	if(bright > 10 || bright < 0){
		printf("invalid command\r\n");
		return;
	}
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, bright);
}
