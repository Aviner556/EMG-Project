#ifndef _LED_
#define _LED_
#include "main.h"

enum LedState
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
};


class LED {
private:
	GPIO_TypeDef * _port;
	uint32_t _pin;
	LedState _state;

public:
	// default constructor
	LED(){
		_port = LD2_GPIO_Port;
		_pin = LD2_Pin;
		_state = STATE_LED_OFF;
	};
	~LED(){}; // destructor

	void ledOn();
	void ledOff();
	void ledChangeState();
	void ledBlink();
	LedState ledGetState();
};


#endif
