#include "Led-PWM.h"
#include "main.h"
#include "stdio.h"


extern TIM_HandleTypeDef htim2; // 1ms


void LedPWM::ledOn()
{
	if(_state == STATE_LED_ON){
		return;
	}
	_state = STATE_LED_ON;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 10);
}


void LedPWM::ledOff()
{
	if(_state == STATE_LED_OFF){
		return;
	}
	_state = STATE_LED_OFF;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
}


void LedPWM::ledBrightness(int bright)
{
	_state = STATE_LED_BRIGHT;
	if(bright <= 10 && bright >= 1){
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, bright);
		return;
	}
	printf("bright most be 1-10\r\n");
}


//replacing "onTimerIntterupt"
void LedPWM::timerFunc()
{
	if(_state == STATE_LED_BLINK){
		_counter++;
		if(_counter >= _maxPeriod){
			if(_blink == 0){
				_blink = 10;
			}
			else{
				_blink = 0;
			}
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, _blink);
			_counter = 0;
		}
	}
}
