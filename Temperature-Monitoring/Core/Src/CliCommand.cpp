#include "CliCommand.h"
#include "Communication.h"
#include "Flash.h"
#include "Rtc.h"
#include "myMain.h"
#include <stdlib.h>
#include <stdio.h>

extern DateTime dateTime;
extern Rtc * rtc;
extern Flash * flash;

extern TEMPLIMIT tempLim;


class setTime : public CliCommand
{
private:
	Rtc * _rtc;

public:

	setTime(Rtc * rtc):_rtc(rtc){};

	void doCommand(const char * param) override
	{
		_rtc->rtcSetTime(&dateTime);
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
		_rtc->rtcGetTime(&dateTime);
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
		if(atof(param) < tempLim.critical){
			tempLim.warning = atof(param);
			_flash->Flash_write(&tempLim);
		}
		else{
			printf("Warning must be less then %f\r\n",tempLim.critical);
		}
	}
};

class setCritical : public CliCommand
{
private:
	Flash * _flash;

public:

	setCritical(Flash * flash):_flash(flash){}

	void doCommand(const char * param) override
	{
		if(atof(param) > tempLim.warning){
			tempLim.critical = atof(param);
			_flash->Flash_write(&tempLim);
		}
		else{
			printf("Critical must be more then %f\r\n",tempLim.warning);
		}
	}
};


void CliCommand_init()
{
	RegisterCommand("settime", new setTime(rtc));
	RegisterCommand("gettime", new getTime(rtc));
	RegisterCommand("setwarning",new setWarning(flash));
	RegisterCommand("setcritical",new setCritical(flash));
	RegisterCommand("help",NULL);
}

