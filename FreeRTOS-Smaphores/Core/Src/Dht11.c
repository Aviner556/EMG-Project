#include "Dht11.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>


extern Dht11 dht;
extern TIM_HandleTypeDef htim6;

extern osSemaphoreId_t DhtSemHandle;
extern osSemaphoreId_t PrintSemHandle;

void Dht11_init(Dht11 * dht)
{
	dht->DhtState = STATE_SLEEP;
	dht->gpioPin = DHT11_Pin;
	dht->gpioPort = DHT11_GPIO_Port;
	memset(dht->DhtBuffer, 0, sizeof(dht->DhtBuffer));
	dht->humidity = 0.0;
	dht->temperature = 0.0;
	dht->checkSum = 0;
	dht->bitCount = 0;
	dht->msCount = 0;
}

/*****************************************************************************/
/*****************************************************************************/
//not working in interrupt mode
/*****************************************************************************/
/*****************************************************************************/

// set the DHT to output mode
void Dht11_setGpioOutput(Dht11 * dht)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = dht->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &GPIO_InitStruct);
}

// set the DHT to input mode
void Dht11_setInput(Dht11 * dht)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = dht->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &GPIO_InitStruct);
}

// waiting the time that received, on the same pin state (0/1)
void waitTime(Dht11 * dht, int pinState, int timeOut)
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == pinState){
		if(__HAL_TIM_GET_COUNTER(&htim6) > timeOut){
			return;
		}
	}
}

void Dht11_Read(Dht11 * dht)
{
	Dht11_setGpioOutput(dht);
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	//MCU lowering the signal for 18ms
	while(__HAL_TIM_GET_COUNTER(&htim6) < 18000){
		//int tim = __HAL_TIM_GET_COUNTER(&htim6);
	}
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);
	Dht11_setInput(dht);

	//MCU raising the signal for 40us
	waitTime(dht, 1, 60);

	//DHT11 lowering the signal for 80us
	waitTime(dht, 0, 90);

	//DHT11 raising the signal for 80us
	waitTime(dht, 1, 90);

	Dht11_reciveData(dht);
}

void Dht11_reciveData(Dht11 * dht)
{
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 8; j++){
			//lowering the signal for 50us before sending
			waitTime(dht, 0, 80);

			//checking how long signal on 1
			waitTime(dht, 1, 100);

			// move itself 1 bit to the left (to write the receiving bit)
			dht->DhtBuffer[i] <<= 1;
			if(__HAL_TIM_GET_COUNTER(&htim6) > 50){ //1 write, 0 ignore
				//writing the data
				dht->DhtBuffer[i] |= 1; //or 1
			}
		}
	}
	int checkSum = dht->DhtBuffer[0] + dht->DhtBuffer[1] + dht->DhtBuffer[2] + dht->DhtBuffer[3];
	if(checkSum == dht->DhtBuffer[4]){
		dht->humidity = dht->DhtBuffer[0] + (dht->DhtBuffer[1]*0.1);
		dht->temperature = dht->DhtBuffer[2] + (dht->DhtBuffer[3]*0.1);
		dht->checkSum = checkSum;


		osSemaphoreRelease(PrintSemHandle);
		//printf("Humidity - %u.%u\r\nTemperature - %u.%u\r\nChekSum - %u\r\n",dht->DhtBuffer[0],dht->DhtBuffer[1],dht->DhtBuffer[2],dht->DhtBuffer[3],dht->DhtBuffer[4]);
	}
	else{
		printf("checksum not match\r\n\n");
	}
}



