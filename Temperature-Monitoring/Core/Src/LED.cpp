#include "LED.h"
#include "main.h"
#include "cmsis_os.h"

extern LED * led;

extern "C" void Entry_LED(void *argument)
{
  /* USER CODE BEGIN Entry_LED */
  /* Infinite loop */
  for(;;)
  {
	  led->ledBlink();
    osDelay(1);
  }
  /* USER CODE END Entry_LED */
}

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


void LED::ledBlink()
{
	if(_state == STATE_LED_BLINK){
		HAL_GPIO_TogglePin(_port, _pin);
		osDelay(500);
	}
}
