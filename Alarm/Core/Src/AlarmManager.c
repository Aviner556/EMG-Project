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

void AlarmManager_add(char * name, int hour, int minutes, int stateRepeat)
{
	if(_cnt_alarms < MAX_ALARMS){
		strcpy(alarms[_cnt_alarms].alarmName, name);
		alarms[_cnt_alarms].time = (hour * 3600) + (minutes * 60);
		alarms[_cnt_alarms].isActive = ON;
		alarms[_cnt_alarms].isOnRepeat = stateRepeat;
		alarms[_cnt_alarms].alarmState = ALARM_STATE_OFF;
		alarms[_cnt_alarms].cntTimerRing = 0;
		alarms[_cnt_alarms].cntTimerWait = 0;
		alarms[_cnt_alarms].cntSnooz = 0;
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
		 if(strcmp(alarms[i].alarmName, name) == 0){
			 if(i == _cnt_alarms-1){
			 	memset(&alarms[i], 0, sizeof(alarms[i]));
			 	_cnt_alarms--;
			 	return;
			 }
			 else{
				alarms[i] = alarms[_cnt_alarms-1];
			 	memset(&alarms[_cnt_alarms-1], 0, sizeof(alarms[_cnt_alarms-1]));
			 	_cnt_alarms--;
				return;
			}
		 }
	}
	printf("alarm not exist\r\n");
}
void AlarmManager_edit(char * time, char * text, bool * stateRepeat);

void AlarmManager_onTimerIntterupt()
{
	int i = AlarmManager_alarmIsOnTime();
	if(i < 0){
		return;
	}
	if(alarms[i].alarmState == ALARM_STATE_OFF){
		Buzzer_start(&buzzer);
		alarms[i].alarmState = ALARM_STATE_RINGING;
	}
}

int AlarmManager_alarmIsOnTime()
{
	for(int i = 0; i < _cnt_alarms; i++){
		if(alarms[i].isActive == 0){
			continue;
		}
		HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0, 1, readBuff, 7, 0Xff);
		if(alarms[i].time == Clock_getTime(readBuff)){
			return i;
		}
	}
	return -1;
}

void AlarmManager_ringOnTimerIntterupt()
{
	for(int i = 0; i < _cnt_alarms; i++){
		if(alarms[i].alarmState == ALARM_STATE_RINGING){
			alarms[i].cntTimerRing++;
		}
		if(alarms[i].cntTimerRing >= 300){
			alarms[i].cntTimerRing = 0;
			Buzzer_stop(&buzzer);
			alarms[i].alarmState = ALARM_STATE_WAITING;
			alarms[i].cntSnooz++;
		}
		if(alarms[i].alarmState == ALARM_STATE_WAITING){
			if(alarms[i].cntSnooz > 2){
				alarms[i].alarmState = ALARM_STATE_OFF;
				alarms[i].cntSnooz = 0;
				return;
			}
			alarms[i].cntTimerWait++;
			if(alarms[i].cntTimerWait >= 600){
				Buzzer_start(&buzzer);
				alarms[i].alarmState = ALARM_STATE_RINGING;
				alarms[i].cntTimerWait = 0;
			}
		}
	}
}















