#include "CliCommand.h"
#include "Communication.h"
#include "Flash.h"
#include "Rtc.h"
#include "myMain.h"
#include <stdlib.h>
#include <stdio.h>

DateTime time;
Rtc * rtc = new Rtc();
Flash * flash;

extern TEMPLIMIT tempLim;


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

class setWarning : public CliCommand
{
private:
	Flash * _flash;

public:

	setWarning(Flash * flash):_flash(flash){}

	void doCommand(const char * param) override
	{
		tempLim.warning = atof(param);
		_flash->Flash_write(&tempLim);
	}
};


void CliCommand_init()
{
	RegisterCommand("settime", new setTime(rtc));
	RegisterCommand("gettime", new getTime(rtc));
	RegisterCommand("setwarining",new setWarning(flash));
	RegisterCommand("help",NULL);
}

