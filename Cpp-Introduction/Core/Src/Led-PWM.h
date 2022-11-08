#ifndef SRC_LED_PWM_H_
#define SRC_LED_PWM_H_


class LedPWM : public LED{
private:
	GPIO_TypeDef * _port;
	uint32_t _pin;
	LedState _state;
	int _counter;
	int _maxPeriod;

public:
	// default constructor
	LedPWM(){
		_port = LD3_GPIO_Port;
		_pin = LD3_Pin;
		_state = STATE_LED_OFF;
		_counter = 0;
		_maxPeriod = 100;
	};
	~LedPWM(){}; // destructor

	void timerFunc(){};

	void ledOn();
	void ledOff();
	void ledChangeState();
	void ledBlink(int maxPeriod);
	void ledBrightness(int bright);
};



#endif /* SRC_LED_PWM_H_ */
