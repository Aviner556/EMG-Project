#include <CLI.h>
#include <LED.h>
#include <buzzer.h>
#include <commTask.h>
#include "stdio.h"

extern LED blue;
extern LED red;
extern BUZZER buzzer;


void cliInit()
{
	registerCommand("ledson",ledOn,&red);
	registerCommand("ledson",ledOn,&blue);
	registerCommand("ledsoff",ledOff,&red);
	registerCommand("ledsoff",ledOff,&blue);
	registerCommand("redledon",ledOn,&red);
	registerCommand("redledoff",ledOff,&red);
	registerCommand("blueledon",ledOn,&blue);
	registerCommand("blueledoff",ledOff,&blue);
	registerCommand("buzzeron",buzzerStart,&buzzer);
	registerCommand("buzzeroff",buzzerStop,&buzzer);
	registerCommand("help",printHelp,NULL);
}
