#include "LED.h"
#include "cmsis_os.h"

void Led_init(Led* led,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led ->counter = 0;
	led ->GPIOx = GPIOx;
	led ->GPIO_Pin = GPIO_Pin;
	led ->period = 0;
	HAL_GPIO_WritePin(led ->GPIOx, led ->GPIO_Pin, 0);
}

void entry_BlueLedBlink(void *argument)
{
  /* USER CODE BEGIN entry_BlueLedBlink */
	Led * led = (Led*)argument;

  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
    osDelay(100);
  }
  /* USER CODE END entry_BlueLedBlink */
}
