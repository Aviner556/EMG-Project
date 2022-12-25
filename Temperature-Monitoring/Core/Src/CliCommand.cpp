#include "CliCommand.h"
#include "Communication.h"
#include "SDCard.h"
#include "Flash.h"
#include "Rtc.h"
#include "myMain.h"
#include <stdlib.h>
#include <stdio.h>

extern DateTime dateTime;
extern Rtc * rtc;
extern Flash * flash;
extern SDCARD * SDC;
//extern Communication * CT;

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
		printf("output: %02d/%02d/%02d Day-%d %02d:%02d:%02d\r\n",dateTime.day,dateTime.month,dateTime.year,dateTime.weekDay,
				dateTime.hours,dateTime.min,dateTime.sec);
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
			_flash->write(&tempLim);
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
			_flash->write(&tempLim);
		}
		else{
			printf("Critical must be more then %f\r\n",tempLim.warning);
		}
	}
};


class printLog : public CliCommand
{

public:

	void doCommand(const char * param) override
	{
		char logName[8] = "log.txt";
		SDC->readSDLog(logName);
	}
};


class clearLog : public CliCommand
{

public:

	void doCommand(const char * param) override
	{
		SDC->clearSDLog();
	}
};


class help : public CliCommand
{

public:

	void doCommand(const char * param) override
	{
		Communication_printHelp();
	}
};


void CliCommand_init()
{
	RegisterCommand("settime", new setTime(rtc));
	RegisterCommand("gettime", new getTime(rtc));
	RegisterCommand("setwarning",new setWarning(flash));
	RegisterCommand("setcritical",new setCritical(flash));
	RegisterCommand("printlog",new printLog());
	RegisterCommand("clearlog",new clearLog());
	RegisterCommand("help",new help());
}

