#ifndef SRC_LED_GPIO_H_
#define SRC_LED_GPIO_H_

#include "Led.h"
#include "main.h"
#include <cstdio>

class LedGpio : public LED{
private:
	GPIO_TypeDef * _port;
	uint32_t _pin;
	int _counter;
	int _maxPeriod;

public:
	// default constructor
	LedGpio(){
		_port = LD3_GPIO_Port;
		_pin = LD3_Pin;
		_state = STATE_LED_OFF;
		_counter = 0;
		_maxPeriod = 100;
	};
	LedGpio(GPIO_TypeDef * port, uint16_t pin):_port(port),_pin(pin){
		_state = STATE_LED_OFF;
		_counter = 0;
		_maxPeriod = 100;
	}
	~LedGpio(){}; // destructor

	void timerFunc();

	void ledOn();
	void ledOff();
	void ledBrightness(int bright){
		printf("try 'bluebright'\r\n");
	};
};


#endif /* SRC_LED_GPIO_H_ */
