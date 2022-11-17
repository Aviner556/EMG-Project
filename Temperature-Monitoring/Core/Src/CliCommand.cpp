#include "CliCommand.h"
#include "Communication.h"
#include "Rtc.h"
#include <stdlib.h>
#include <stdio.h>

extern DateTime * time;

class setTime : public CliCommand
{
private:
	Rtc * _rtc;

public:

	void doCommand(const char * param) override
	{
		_rtc->rtcSetTime(time);
	}
};


class getTime : public CliCommand
{
private:
	Rtc * _rtc;

public:

	void doCommand(const char * param) override
	{
		_rtc->rtcGetTime(time);
	}
};



void CliCommand_init()
{
	RegisterCommand("settime", NULL);
	RegisterCommand("gettime", NULL);
	RegisterCommand("help",NULL);
}

