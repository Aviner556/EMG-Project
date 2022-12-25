#ifndef SRC_LED_GPIO_H_
#define SRC_LED_GPIO_H_

#include "main.h"
#include <cstdio>

enum LedState
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
};

class LED
{
private:
	GPIO_TypeDef * _port;
	uint32_t _pin;
	LedState _state = STATE_LED_OFF;

public:
	// default constructor
	LED()
	{
		_port = LD14_GPIO_Port;
		_pin = LD14_Pin;
		_state = STATE_LED_OFF;
	}
	LED(GPIO_TypeDef * port, uint16_t pin):_port(port),_pin(pin)
	{
		_state = STATE_LED_OFF;
	}
	~LED(){} // destructor

	uint32_t getPin()
	{
		return _pin;
	}
	GPIO_TypeDef * getPort()
	{
		return _port;
	}
	LedState getState()
	{
		return _state;
	}
	void ledOn();
	void ledOff();
	void ledBlink();
	void setLedBlink()
	{
		_state = STATE_LED_BLINK;
	};
};


#endif /* SRC_LED_GPIO_H_ */
