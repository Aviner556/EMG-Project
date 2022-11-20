#include "CliCommand.h"
#include "Communication.h"
#include "Rtc.h"
#include <stdlib.h>
#include <stdio.h>

extern DateTime time;
extern Rtc * rtc;

class setTime : public CliCommand
{
private:
	Rtc * _rtc;

public:

	setTime(Rtc * rtc):_rtc(rtc){};

	void doCommand(const char * param) override
	{
		_rtc->rtcSetTime(&time);
	}
};


class getTime : public CliCommand
{
private:
	Rtc * _rtc;

public:

	getTime(Rtc * rtc):_rtc(rtc){};

	void doCommand(const char * param) override
	{
		_rtc->rtcGetTime(&time);
	}
};



void CliCommand_init()
{
	RegisterCommand("settime", new setTime(rtc));
	RegisterCommand("gettime", new getTime(rtc));
	RegisterCommand("help",NULL);
}

