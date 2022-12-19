#ifndef _Dht11_
#define _Dht11_

#include "main.h"
#include <string.h>


class DHT
{
private:
	GPIO_TypeDef * _gpioPort;
	uint16_t _gpioPin;
	uint8_t _DhtBuffer[5];
	double _temperature;
	double _humidity;

public:
	DHT(){
		_gpioPort = DHT11_GPIO_Port;
		_gpioPin = DHT11_Pin;
		memset(_DhtBuffer, 0, sizeof(_DhtBuffer));
		_temperature = 0.0;
		_humidity = 0.0;
	};

	~DHT(){};

	void read();
	void reciveData();
	void setInput();
	void setGpioOutput();
	void waitTime(GPIO_PinState pinState, uint32_t timeOut);

	double getTemp()
	{
		/****
		 * using _humidity for easy checking
		 * need to be _temperature!!!
		 ****/
		return _temperature;
	};
};


#endif
