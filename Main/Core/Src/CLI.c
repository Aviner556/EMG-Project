#include <Cli.h>
#include <Led.h>
#include <Buzzer.h>
#include <Communication.h>
#include "stdio.h"
#include <stdlib.h>

extern Led blue;
extern Led red;
extern Buzzer buzzer;

void Cli_cmdLedOn(void * obj, char * param)
{
	Led * led = (Led *)obj;
	Led_on(led);
}

void Cli_cmdLedOff(void * obj, char * param)
{
	Led * led = (Led *)obj;
	Led_off(led);
}

void Cli_cmdLedBlink(void * obj, char * param)
{
	Led * led = (Led *)obj;
	int maxPeriod = atoi(param);
	Led_blink(led,maxPeriod);
}

void Cli_cmdBuzzerOn(void * obj, char * param)
{
	Buzzer * buzzer = (Buzzer *)obj;
	Buzzer_start(buzzer);
}

void Cli_cmdBuzzerOff(void * obj, char * param)
{
	Buzzer * buzzer = (Buzzer *)obj;
	Buzzer_stop(buzzer);
}

void Cli_init()
{
	RegisterCommand("redledon",Cli_cmdLedOn,&red);
	RegisterCommand("redledoff",Cli_cmdLedOff,&red);
	RegisterCommand("redledblink",Cli_cmdLedBlink,&red);
	RegisterCommand("blueledon",Cli_cmdLedOn,&blue);
	RegisterCommand("blueledoff",Cli_cmdLedOff,&blue);
	RegisterCommand("blueledblink",Cli_cmdLedBlink,&blue);
	RegisterCommand("buzzeron",Cli_cmdBuzzerOn,&buzzer);
	RegisterCommand("buzzeroff",Cli_cmdBuzzerOff,&buzzer);
	RegisterCommand("help",Communication_printHelp,NULL);
}
