#include "CliCommand.h"
#include "Communication.h"
#include "Led.h"

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
		_led->ledBlink();
	}
};


void CliCommand_init()
{
	RegisterCommand("ledon", new ledon(&blueLed));
	RegisterCommand("ledoff",new ledoff(&blueLed));
	RegisterCommand("ledblink",new ledBlink(&blueLed));
	RegisterCommand("help",NULL);
}

