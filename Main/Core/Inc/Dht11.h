#ifndef _Dht11_
#define _Dht11_

#include "main.h"

typedef struct Dht11_
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	double temperature;
	double humidity;
	int checkSum;
}Dht11;

void Dht11_init(Dht11 * dht);
void Dht11_reciveData(Dht11 * dht);
void Dht11_Start(Dht11 * dht);
void Dht11_setInput(Dht11 * dht);
void Dht11_setOutput(Dht11 * dht);
//void Dht11_printTempHum(Dht11 * dht);

#endif
