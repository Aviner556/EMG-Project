#include "main.h"
#include "Buttons.h"


void Button::Button_interrupt()
{
	if(HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == 0){
		_state = STATE_PRESS;
	}
	else if(HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == 1){
		_state = STATE_NONE;
	}
}
