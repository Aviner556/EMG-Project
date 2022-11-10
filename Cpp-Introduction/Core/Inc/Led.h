#ifndef _LED_
#define _LED_
#include "main.h"
#include "MainTimerIT.h"

enum LedState
{
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK,
	STATE_LED_BRIGHT
};

class LED : public TimerTask{
private:
	GPIO_TypeDef * _port;
	uint32_t _pin;
	int _counter;
	int _maxPeriod;

protected:
	LedState _state;

public:
	// default constructor
	LED(){
		_port = LD3_GPIO_Port;
		_pin = LD3_Pin;
		_state = STATE_LED_OFF;
		_counter = 0;
		_maxPeriod = 100;
	};
	~LED(){}; // destructor

	virtual void timerFunc() = 0;

	virtual void ledOn() = 0;
	virtual void ledOff() = 0;
	virtual void ledBrightness(int bright) = 0;

	void ledBlink(int maxPeriod);
	LedState ledGetState();

};


#endif
