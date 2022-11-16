#include "Dht11.h"
#include "main.h"

extern TIM_HandleTypeDef htim16; // 1us


void DHT::Dht11_setInput()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = _gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(_gpioPort, &GPIO_InitStruct);
}

void DHT::Dht11_setGpioOutput()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = _gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(_gpioPort, &GPIO_InitStruct);
}

void DHT::waitTime(GPIO_PinState pinState, uint32_t timeOut)
{
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	while(HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == pinState){
		if(__HAL_TIM_GET_COUNTER(&htim16) > timeOut){
			return;
		}
	}
}

void DHT::Dht11_Read()
{
	Dht11_setGpioOutput();
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	//MCU lowering the signal for 18ms
	while(__HAL_TIM_GET_COUNTER(&htim16) < 18000){}
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
	Dht11_setInput();

	//MCU raising the signal for 40us
	waitTime(GPIO_PIN_SET, 60);

	//DHT11 lowering the signal for 80us
	waitTime(GPIO_PIN_RESET, 90);

	//DHT11 raising the signal for 80us
	waitTime(GPIO_PIN_SET, 90);

	Dht11_reciveData();
}

void DHT::Dht11_reciveData()
{
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 8; j++){
			//lowering the signal for 50us before sending
			waitTime(GPIO_PIN_RESET, 80);

			//checking how long signal on 1
			waitTime(GPIO_PIN_SET, 100);

			//writing the data
			_DhtBuffer[i] <<= 1;
			if(__HAL_TIM_GET_COUNTER(&htim16) > 50){ //1 write, 0 ignore
				_DhtBuffer[i] |= 1; //or 1
			}
		}
	}
	int checkSum = _DhtBuffer[0] + _DhtBuffer[1] + _DhtBuffer[2] + _DhtBuffer[3];
	if(checkSum == _DhtBuffer[4]){
		_humidity = _DhtBuffer[0] + (_DhtBuffer[1]*0.1);
		_temperature = _DhtBuffer[2] + (_DhtBuffer[3]*0.1);
	}
}



