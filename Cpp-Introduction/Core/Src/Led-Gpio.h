#ifndef SRC_LED_GPIO_H_
#define SRC_LED_GPIO_H_


class LedGpio : public LED{
private:
	LedState _state;
	int _counter;
	int _maxPeriod;

public:
	// default constructor
	LedGpio(){
		_state = STATE_LED_OFF;
		_counter = 0;
		_maxPeriod = 100;
	};
	~LedGpio(){}; // destructor

	void timerFunc(){};

	void ledOn();
	void ledOff();
	void ledBlink(int maxPeriod);
	void ledBrightness(int bright);
	LedState ledGetState(){};
};


#endif /* SRC_LED_GPIO_H_ */
