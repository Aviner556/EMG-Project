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
	registerCommand("ledon",ledOn,&red);
	registerCommand("ledoff",ledOff,&red);
	registerCommand("buzzeron",buzzerStart,&buzzer);
	registerCommand("buzzeroff",buzzerStop,&buzzer);
}
