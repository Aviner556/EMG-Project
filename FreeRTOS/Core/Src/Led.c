#include "Led.h"
#include "main.h"
#include "cmsis_os.h" //include freeROTS


void Led_init(Led * led,GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin)
{
	led->gpioPort = GPIOx;
	led->gpioPin = GPIO_Pin;
	led->ledDelay = 100;
}

void entry_BlueLedBlink(void *argument)
{
  /* USER CODE BEGIN entry_BlueLedBlink */
	Led * blueLed = (Led *)argument;
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  osDelay(blueLed->ledDelay);
  }
  /* USER CODE END entry_BlueLedBlink */
}

void entry_RedLedBlink(void *argument)
{
  /* USER CODE BEGIN entry_RedLedBlink */
	Led * redLed = (Led *)argument;
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	  osDelay(redLed->ledDelay);
  }
  /* USER CODE END entry_RedLedBlink */
}
