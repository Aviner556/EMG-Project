#ifndef _Dht11_
#define _Dht11_

#include "main.h"
#include "TimerTask.h"
#include <string.h>

typedef enum _Dht11State
{
	STATE_SLEEP,
	STATE_WAKEUP_START,
	STATE_WAKEUP_END,
	STATE_WAITING_RESPONSE_START,
	STATE_WAITING_RESPONSE_END,
	STATE_RECIVING_BIT,
	STATE_HAS_DATA,
}Dht11State;

class DHT : public TimerTask
{
private:
		Dht11State _DhtState;
		GPIO_TypeDef * _gpioPort;
		uint16_t _gpioPin;
		uint8_t _DhtBuffer[5];
		double _temperature;
		double _humidity;
		int _bitCount;
		int _msCount;
public:
		DHT(){
			_DhtState = STATE_SLEEP;
			_gpioPort = DHT11_GPIO_Port;
			_gpioPin = DHT11_Pin;
			memset(_DhtBuffer, 0, sizeof(_DhtBuffer));
			_temperature = 0.0;
			_humidity = 0.0;
			_bitCount = 0;
			_msCount = 0;
		};
		~DHT(){};

		void timerFunc();

		void Dht11_Read();
		void Dht11_reciveData();
		void Dht11_setInput();
		void Dht11_setGpioOutput();
		void waitTime(GPIO_PinState pinState, uint32_t timeOut);
};


#endif
