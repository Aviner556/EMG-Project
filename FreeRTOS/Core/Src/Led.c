#include "Led.h"
#include "main.h"
#include "cmsis_os.h" //include freeROTS

// tim2 is the PWM clock that attached to blue led
extern TIM_HandleTypeDef htim2;
extern osMessageQueueId_t myQueue01Handle;

void Led_init(Led * led,GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin)
{
	led->gpioPort = GPIOx;
	led->gpioPin = GPIO_Pin;
	led->ledDelay = 100;
	led->ledBright = 10;
}

void entry_BlueLedBlink(void * argument)
{
  /* USER CODE BEGIN entry_BlueLedBlink */
	int delay = 500;
	uint16_t msg;
	uint16_t brightness = 10;
	osStatus_t status;

	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	//Led * blueLed = (Led *)argument; // when the led work on PWM it can work on GPIO
  /* Infinite loop */
  for(;;)
  {
	  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); // when the led work on PWM it can work on GPIO

	  // turn off the light
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);

	  // checking if the queue not empty. waiting until the timeout
	  status = osMessageQueueGet(myQueue01Handle, &msg, 0, 500);
	  if(status == osOK){
		  brightness = msg;
	  }
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, brightness*10);
	  osDelay(delay);
  }
  /* USER CODE END entry_BlueLedBlink */
}

void entry_RedLedBlink(void * argument)
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




///* USER CODE END Header_entry_BlueLedBrightness */
//void entry_BlueLedBrightness(void *argument)
//{
//  /* USER CODE BEGIN entry_BlueLedBrightness */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
//  /* USER CODE END entry_BlueLedBrightness */
//}

//void Led_brightness(int bright)
//{
//	if(bright > 10 || bright < 0){
//		//printf("invalid command\r\n");
//		return;
//	}
//	HAL_TIM_Base_Start_IT(&htim2);
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, bright);
//}


