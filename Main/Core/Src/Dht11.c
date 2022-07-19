#include "Dht11.h"
#include "main.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim16;
extern Dht11 TempHum;

uint8_t DhtBuffer[5] = {0};

void Dht11_init(Dht11 * dht)
{
	dht->gpioPin = Dht11_Pin;
	dht->gpioPort = Dht11_GPIO_Port;
	dht->humidity = 0.0;
	dht->temperature = 0.0;
	//dht->checksum = 0;
}

void Dht11_setOutput(Dht11 * dht)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = dht->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &GPIO_InitStruct);
}

void Dht11_setInput(Dht11 * dht)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = dht->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &GPIO_InitStruct);
}

void Dht11_Start(Dht11 * dht)
{
	Dht11_setOutput(dht);
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	//MCU lowering the signal for 18ms
	while(__HAL_TIM_GET_COUNTER(&htim16) < 18500) {
	}

	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);
	Dht11_setInput(dht);
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	//MCU raising the signal for 40us
	while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == 1){
		if(__HAL_TIM_GET_COUNTER(&htim16) > 60){
			return;
		}
	}
	//DHT11 lowering the signal for 80us
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == 0){
		if(__HAL_TIM_GET_COUNTER(&htim16) > 90){
			return;
		}
	}
	//DHT11 raising the signal for 80us
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == 1){
		if(__HAL_TIM_GET_COUNTER(&htim16) > 90){
			return;
		}
	}
	Dht11_reciveData(dht);
}

void Dht11_reciveData(Dht11 * dht)
{
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 8; j++){
			__HAL_TIM_SET_COUNTER(&htim16, 0);
			while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == 0){
				if(__HAL_TIM_GET_COUNTER(&htim16) > 80){
					return;
				}
			}
			__HAL_TIM_SET_COUNTER(&htim16, 0);
			while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == 1){
				if(__HAL_TIM_GET_COUNTER(&htim16) > 100){
					return;
				}
			}
			DhtBuffer[i] <<= 1;
			if(__HAL_TIM_GET_COUNTER(&htim16) > 50){
				DhtBuffer[i] |= 1;
			}
		}
	}
	int checkSum = DhtBuffer[0] + DhtBuffer[1] + DhtBuffer[2] + DhtBuffer[3];
	if(checkSum == DhtBuffer[4]){
		dht->humidity = DhtBuffer[0] + (DhtBuffer[1]*0.1);
		dht->temperature = DhtBuffer[2] + (DhtBuffer[3]*0.1);
		dht->checkSum = checkSum;

		printf("Humidity - %u.%u\r\nTemperature - %u.%u\r\nChekSum - %u\r\n",DhtBuffer[0],DhtBuffer[1],DhtBuffer[2],DhtBuffer[3],DhtBuffer[4]);
		//Dht11_printTempHum(dht);
	}
}


//void Dht11_printTempHum(Dht11 * dht)
//{
//	printf("Humidity - %f\r\nTemperature - %f\r\nChekSum - %d\r\n",dht.humidity,dht.temperature,dht.checkSum);
//}




