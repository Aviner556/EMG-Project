#include "Dht11.h"
#include "MainTimerIT.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

extern TIM_HandleTypeDef htim16;
extern Dht11 TempHum;


void Dht11_init(Dht11 * dht)
{
	dht->DhtState = STATE_SLEEP;
	dht->gpioPin = Dht11_Pin;
	dht->gpioPort = Dht11_GPIO_Port;
	memset(dht->DhtBuffer, 0, sizeof(dht->DhtBuffer));
	dht->humidity = 0.0;
	dht->temperature = 0.0;
	dht->checkSum = 0;
	dht->bitCount = 0;
	dht->msCount = 0;
}

void Dht11_setGpioOutput(Dht11 * dht)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = dht->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &GPIO_InitStruct);
}

void Dht11_setGpioExti(Dht11 * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin = dht->gpioPin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(dht->gpioPort, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void Dht11_start(Dht11 * dht)
{
	if(dht->DhtState == STATE_SLEEP){
		MainTimerIT_registerCallback(Dht11_onTimerInterrupt, dht);
		Dht11_setGpioOutput(dht);
		HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
		__HAL_TIM_SET_COUNTER(&htim16, 0);
		//MCU lowering the signal for 18ms
		dht->msCount = 0;
		dht->DhtState = STATE_WAKEUP_START;
	}
	else if(dht->DhtState == STATE_WAKEUP_END){
		HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);
		Dht11_setGpioExti(dht);
		dht->DhtState = STATE_WAITING_RESPONSE_START;
	}
}

void Dht11_onGpioInterrupt(Dht11 * dht, uint16_t pin)
{
	if(dht->DhtState == STATE_WAITING_RESPONSE_START){
		dht->DhtState = STATE_WAITING_RESPONSE_END;
	}
	else if(dht->DhtState == STATE_WAITING_RESPONSE_END){
		dht->DhtState = STATE_RECIVING_BIT;
		__HAL_TIM_SET_COUNTER(&htim16, 0);
	}
	else if(dht->DhtState == STATE_RECIVING_BIT){
		Dht11_startRead(dht);
	}
}

void Dht11_onTimerInterrupt(void * obj)
{
	Dht11 * dht = (Dht11 *)obj;
	if(dht->DhtState == STATE_WAKEUP_START){
		dht->msCount++;
	}
	if(dht->msCount >= 18){
		MainTimerIT_registerCallbackRemove(Dht11_onTimerInterrupt, dht);
		dht->DhtState = STATE_WAKEUP_END;
		dht->msCount = 0;
		Dht11_start(dht);
	}
}

void Dht11_startRead(Dht11 * dht)
{
	dht->DhtBuffer[dht->bitCount/8] <<= 1;
	dht->DhtBuffer[dht->bitCount/8] |= Dht11_returnedValue(dht);
	dht->bitCount++;
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	if(dht->bitCount >= 40){
		dht->DhtState = STATE_HAS_DATA;
		dht->humidity = dht->DhtBuffer[0]+(dht->DhtBuffer[1]*0.1);
		dht->temperature = dht->DhtBuffer[2]+(dht->DhtBuffer[3]*0.1);
		dht->checkSum = dht->DhtBuffer[4];
	}
}

int Dht11_returnedValue(Dht11 * dht)
{
	if(__HAL_TIM_GET_COUNTER(&htim16) > 100){ //1 write, 0 ignore
		return 1;
	}
	return 0;
}

void Dht11_hasData(Dht11 * dht)
{
	if(dht->DhtState == STATE_HAS_DATA){
		Dht11_print(dht);
		dht->DhtState = STATE_SLEEP;
	}
}

void Dht11_print(Dht11 * dht)
{
	printf("Humidity - %.2f\r\nTemperature - %.2f\r\nChekSum - %d\r\n\n",dht->humidity,dht->temperature,dht->checkSum);
}




/*****************************************************************************/
//not working in interrupt mode

void Dht11_setInput(Dht11 * dht)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = dht->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &GPIO_InitStruct);
}

void waitTime(Dht11 * dht, int pinState, int timeOut)
{
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	while(HAL_GPIO_ReadPin(dht->gpioPort, dht->gpioPin) == pinState){
		if(__HAL_TIM_GET_COUNTER(&htim16) > timeOut){
			return;
		}
	}
}

void Dht11_Read(Dht11 * dht)
{
	Dht11_setGpioOutput(dht);
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	//MCU lowering the signal for 18ms
	while(__HAL_TIM_GET_COUNTER(&htim16) < 18000){
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

			//writing the data
			dht->DhtBuffer[i] <<= 1;
			if(__HAL_TIM_GET_COUNTER(&htim16) > 50){ //1 write, 0 ignore
				dht->DhtBuffer[i] |= 1; //or 1
			}
		}
	}
	int checkSum = dht->DhtBuffer[0] + dht->DhtBuffer[1] + dht->DhtBuffer[2] + dht->DhtBuffer[3];
	if(checkSum == dht->DhtBuffer[4]){
		dht->humidity = dht->DhtBuffer[0] + (dht->DhtBuffer[1]*0.1);
		dht->temperature = dht->DhtBuffer[2] + (dht->DhtBuffer[3]*0.1);
		dht->checkSum = checkSum;

		printf("Humidity - %u.%u\r\nTemperature - %u.%u\r\nChekSum - %u\r\n",dht->DhtBuffer[0],dht->DhtBuffer[1],dht->DhtBuffer[2],dht->DhtBuffer[3],dht->DhtBuffer[4]);
	}
}



