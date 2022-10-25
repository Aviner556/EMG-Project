#include "Buttons.h"
#include "Buzzer.h"
#include "Clock.h"
#include "AlarmManager.h"
#include "Communication.h"
#include "Flash.h"
#include "main.h"
#include <stdio.h>
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim16;

Button B2;
Buzzer buzzer;
Flash flashRW;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

// button interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	AlarmManager_stopRing();
}


/* USER CODE END Header_entry_AlarmManager */
void entry_AlarmManager(void *argument)
{
  /* USER CODE BEGIN entry_AlarmManager */
	Button_init(&B2,B2_GPIO_Port,B2_Pin);

	Buzzer_init(&buzzer);

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);

	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

	AlarmManager_initArray();
	Flash_init(&flashRW);

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END entry_AlarmManager */
}
