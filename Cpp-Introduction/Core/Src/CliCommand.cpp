#include "CliCommand.h"
#include "Communication.h"
#include "Led.h"
#include <stdlib.h>
#include <stdio.h>

extern LED blueLed;

class ledon : public CliCommand
{
private:
	LED * _led;

public:
	ledon(LED * led):_led(led){};

	void doCommand(const char * param) override
	{
		_led->ledOn();
	}
};


class ledoff : public CliCommand
{
private:
	LED * _led;

public:
	ledoff(LED * led):_led(led){};

	void doCommand(const char * param) override
	{
		_led->ledOff();
	}
};


class ledBlink : public CliCommand
{
private:
	LED * _led;

public:
	ledBlink(LED * led):_led(led){};

	void doCommand(const char * param)
	{
		if(atoi(param) > 0){
			_led->ledBlink(atoi(param));
		}
		else{
			param = "100";
			_led->ledBlink(atoi(param));
			printf("blink set to 100\r\n");
		}
	}
};


class ledBright : public CliCommand
{
private:
	LED * _led;

public:
	ledBright(LED * led):_led(led){};

	void doCommand(const char * param) override
	{
		_led->ledBrightness(atoi(param));
	}
};


void CliCommand_init()
{
	RegisterCommand("ledon", new ledon(&blueLed));
	RegisterCommand("ledoff",new ledoff(&blueLed));
	RegisterCommand("ledblink",new ledBlink(&blueLed));
	RegisterCommand("ledbright",new ledBright(&blueLed));
	RegisterCommand("help",NULL);
}

