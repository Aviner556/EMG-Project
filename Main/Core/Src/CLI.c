#include "Cli.h"
#include "Led.h"
#include "Buzzer.h"
#include "Dht11.h"
#include "Clock.h"
#include "Communication.h"
#include "Flash.h"
#include <stdio.h>
#include <stdlib.h>

extern Led blue;
extern Led red;
extern Buzzer buzzer;
extern Dht11 TempHum;
extern Clock clc1;
extern Flash flashRW;

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

void Cli_cmdDht11Start(void * obj, char * param)
{
	Dht11 * dht = (Dht11 *)obj;
	Dht11_start(dht);
}

void Cli_cmdDht11Print(void * obj, char * param)
{
	Dht11 * dht = (Dht11 *)obj;
	Dht11_print(dht);
}

void Cli_cmdClockShowTime(void * obj, char * param)
{
	Clock * clock = (Clock *)obj;
	Clock_showTime(clock);
}

void Cli_cmdFlashEraseWrite(void * obj, char * param)
{
	Flash * flashRW = (Flash *)obj;
	Flash_erase(flashRW);
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
	RegisterCommand("dhtstart",Cli_cmdDht11Start,&TempHum);
	RegisterCommand("dhtprint",Cli_cmdDht11Print,&TempHum);
	RegisterCommand("showtime",Cli_cmdClockShowTime,&clc1);
	RegisterCommand("flash",Cli_cmdFlashEraseWrite,&flashRW);
	RegisterCommand("help",Communication_printHelp,NULL);
}
