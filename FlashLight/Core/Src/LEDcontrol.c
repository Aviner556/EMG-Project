#include "LEDcontrol.h"
#include "main.h"

extern TIM_HandleTypeDef htim6;

void stop()
{
	HAL_TIM_Base_Stop_IT(&htim6);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
}

void start()
{
	HAL_TIM_Base_Stop_IT(&htim6);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
}

void DIM()
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim6, 5);
	HAL_TIM_Base_Start_IT(&htim6);
}

void flashing()
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim6, 5000);
	HAL_TIM_Base_Start_IT(&htim6);
}

int brightCnt = 0;
int brightLevel;
void setBrightness(int brightness)
{
	if(brightness < 0 || brightness > 10 ){
		printf("wrong parameter\r\n");
		return;
	}
	brightLevel = brightness;
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim6, 10);
	HAL_TIM_Base_Start_IT(&htim6);
}

