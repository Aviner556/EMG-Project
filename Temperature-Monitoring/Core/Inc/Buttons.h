#ifndef _Buttons_
#define _Buttons_

#include "main.h"

enum Button_State
{
	STATE_NONE,
	STATE_PRESS
};

class Button
{
private:
	Button_State _state;
	GPIO_TypeDef * _gpioPort;
	uint16_t _gpioPin;
public:
	Button()
	{
		_gpioPort = B2_GPIO_Port;
		_gpioPin = B2_Pin;
		_state = STATE_NONE;
	}
	~Button(){}

	void Button_interrupt();
};


#endif
