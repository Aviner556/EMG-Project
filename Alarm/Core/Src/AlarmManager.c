#include "AlarmManager.h"
#include "Clock.h"
#include "Buzzer.h"
#include <string.h>
#include <stdio.h>
#include "main.h"

#define MAX_ALARMS 5

extern Buzzer buzzer;
extern I2C_HandleTypeDef hi2c1;
Alarm alarms[MAX_ALARMS];
static int _cnt_alarms = 0;
uint8_t readBuff[7];

void AlarmManager_init(){
	memset(alarms, 0, sizeof(alarms));
}

void AlarmManager_add(char * name, int hour, int minutes, bool stateRepeat)
{
	if(_cnt_alarms < MAX_ALARMS){
		strcpy(alarms[_cnt_alarms].alarmName, name);
		alarms[_cnt_alarms].time = (hour * 3600) + (minutes * 60);
		alarms[_cnt_alarms].isActive = ON;
		alarms[_cnt_alarms].isOnRepeat = stateRepeat;
		_cnt_alarms++;
	}
	else{
		printf("no room for the alarm");
	}
}

void AlarmManager_delete(char * name)
{
	if(_cnt_alarms == 0){
		return;
	}
	for(int i = 0; i < MAX_ALARMS; i++){
		 if(alarms[i].alarmName == name){
			 if(i == _cnt_alarms-1){
			 	memset(&alarms[i], 0, sizeof(alarms[i]));
			 	_cnt_alarms--;
			 	return;
			 }
			 else{
				alarms[i] = alarms[_cnt_alarms-1];
			 	memset(&_cnt_alarms-1, 0, sizeof(_cnt_alarms-1));
			 	_cnt_alarms--;
				return;
			}
		 }
	}
}
void AlarmManager_edit(char * time, char * text, bool * stateRepeat);

void AlarmManager_onTimerIntterupt()
{
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0, 1, readBuff, 7, 0Xff);
	for(int i = 0; i < _cnt_alarms; i++){
		if(alarms[i].isActive == 0){
			continue;
		}
		if(alarms[i].time == Clock_getTime(readBuff)){
			AlarmManager_ring(alarms[i]);
		}
	}
}

void AlarmManager_ring(Alarm alarm)
{
	Buzzer_start(&buzzer);
}















