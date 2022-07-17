#ifndef _Dht11_
#define _Dht11_

typedef enum Dht11State_
{
	STATE_OUTPUT,
	STATE_INPUT,
}Dht11State;

typedef struct Dht11_
{
	double temperature;
	double humidity;
}Dht11;

#endif
