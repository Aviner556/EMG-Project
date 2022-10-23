#include "Cli.h"
#include "Buzzer.h"
#include "Clock.h"
#include "AlarmManager.h"
#include "Communication.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>


extern uint8_t readBuff[7];
extern I2C_HandleTypeDef hi2c1;


void Cli_AlarmManager_add(void * obj)
{
	Alarm * alarm = (Alarm *)obj;
	AlarmManager_add(alarm);
}

void Cli_AlarmManager_edit(void * obj)
{
	Alarm * alarm = (Alarm *)obj;
	AlarmManager_edit(alarm);
}

void Cli_AlarmManager_delete(void * obj)
{
	Alarm * alarm = (Alarm *)obj;
	AlarmManager_delete(alarm);
}

void Cli_AlarmManager_print_time(void * obj)
{
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0, 1, readBuff, 7, 0Xff);
	Clock_printTime(readBuff);
}

void Cli_AlarmManager_print_alarms(void * obj)
{
	AlarmManager_printAllAlarms();
}

void Cli_init()
{
	RegisterCommand("add", Cli_AlarmManager_add);
	RegisterCommand("edit", Cli_AlarmManager_edit);
	RegisterCommand("delete", Cli_AlarmManager_delete);
	RegisterCommand("time", Cli_AlarmManager_print_time);
	RegisterCommand("alarms", Cli_AlarmManager_print_alarms);
}

