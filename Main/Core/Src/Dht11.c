#include "Dht11.h"
#include "main.h"

extern TIM_HandleTypeDef htim16;
extern GPIO_InitTypeDef GPIO_InitStruct;

Dht11 TempHum;

void Dht11_setOutput()
{
	GPIO_InitStruct.Pin = Dht11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Dht11_GPIO_Port, &GPIO_InitStruct);
}

void Dht11_setInput()
{
	GPIO_InitStruct.Pin = Dht11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Dht11_GPIO_Port, &GPIO_InitStruct);
}

void Dht11_Start()
{
	int res = 0;
	HAL_GPIO_WritePin(Dht11_GPIO_Port, Dht11_Pin, 1);
	//lowering the signal
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);
	HAL_GPIO_WritePin(Dht11_GPIO_Port, Dht11_Pin, 0);
	while(res < 18500){
		res = __HAL_TIM_GET_COUNTER(&htim16);
	}
	//raising the signal
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);
	HAL_GPIO_WritePin(Dht11_GPIO_Port, Dht11_Pin, 1);
	Dht11_setInput();
	while(res < 40){
		res = __HAL_TIM_GET_COUNTER(&htim16);
	}


}

