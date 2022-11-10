#ifndef SRC_LED_PWM_H_
#define SRC_LED_PWM_H_

#include "Led.h"


class LedPWM : public LED{
private:
	TIM_HandleTypeDef * _htim;
	unsigned int _timChannel;
	LedState _state;
	int _counter;
	int _maxPeriod;
	int _blink;

public:
	// default constructor
	LedPWM(){
		_state = LED::ledGetState();
		_counter = 0;
		_maxPeriod = 100;
		_blink = 0;
	};
	LedPWM(TIM_HandleTypeDef * htim, unsigned int timChannel):_htim(htim),_timChannel(timChannel){
		_state = LED::ledGetState();
		_counter = 0;
		_maxPeriod = 100;
		_blink = 0;
	}
	~LedPWM(){}; // destructor

	void timerFunc();

	void ledOn();
	void ledOff();
	void ledBlink(int maxPeriod){};
	void ledBrightness(int bright);
};



#endif /* SRC_LED_PWM_H_ */
