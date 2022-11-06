#ifndef _buttons_
#define _buttons_
#include "main.h"

class Button{
private:
	GPIO_TypeDef* _port;
	uint16_t _pin;
public:
	// default constructor
	Button(){
		_port = B2_GPIO_Port;
		_pin = B2_Pin;
	};
	~Button() {} // destructor
};



#endif
