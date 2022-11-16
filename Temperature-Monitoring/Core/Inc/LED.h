#ifndef SRC_LED_GPIO_H_
#define SRC_LED_GPIO_H_

#include "TimerTask.h"
#include "main.h"
#include <cstdio>

enum LedState
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
};

class LED : public TimerTask{
private:
	GPIO_TypeDef * _port;
	uint32_t _pin;
	LedState _state = STATE_LED_OFF;

public:
	// default constructor
	LED(){
		_port = LD3_GPIO_Port;
		_pin = LD3_Pin;
		_state = STATE_LED_OFF;
	};
	LED(GPIO_TypeDef * port, uint16_t pin):_port(port),_pin(pin){
		_state = STATE_LED_OFF;
		_counter = 0;
		_maxPeriod = 100;
	}
	~LED(){}; // destructor

	void timerFunc();

	void ledOn();
	void ledOff();
	void ledBlink();
};


#endif /* SRC_LED_GPIO_H_ */