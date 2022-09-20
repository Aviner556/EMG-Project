#ifndef _Dht11_
#define _Dht11_

#include "main.h"

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

typedef struct Dht11_
{
	Dht11State DhtState;
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	uint8_t DhtBuffer[5];
	double temperature;
	double humidity;
	int checkSum;
	int bitCount;
	int msCount;
}Dht11;

void Dht11_init(Dht11 * dht);
void Dht11_Read(Dht11 * dht);
void Dht11_reciveData(Dht11 * dht);
void Dht11_setInput(Dht11 * dht);
void Dht11_setGpioOutput(Dht11 * dht);
void waitTime(Dht11 * dht, int pinState, int timeOut);


#endif
