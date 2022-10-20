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
	/*
	 * checking if the time is valid
	 */
	if (hour>24|| hour<1 || minutes>59){ //still need to check
		printf("Invalid hour\r\n");
		return;
	}

	/*
	 * checking if there are free space for more alarms
	 */
	if(_cnt_alarms < MAX_ALARMS){
		strcpy(alarms[_cnt_alarms].alarmName, name);
		// converting to seconds
		alarms[_cnt_alarms].time = (hour * 3600) + (minutes * 60);
		alarms[_cnt_alarms].isActive = ON;
		alarms[_cnt_alarms].isOnRepeat = stateRepeat; // 0 = off, 1 = on
		alarms[_cnt_alarms].alarmState = ALARM_STATE_OFF;
		alarms[_cnt_alarms].cntTimerRing = 0;
		alarms[_cnt_alarms].cntTimerWait = 0;
		alarms[_cnt_alarms].cntSnooz = 0;
		_cnt_alarms++;
		printf("added successfully\r\n");
	}
	else{
		printf("no more room for the alarm\r\n");
	}
}

/*
 * received the name of the alarm we wish to delete. if there is more then one with the same name,
 * the first in the list will be deleted.
 */
void AlarmManager_delete(char * name)
{
	if(_cnt_alarms == 0){
		printf("there are no alarms");
		return;
	}
	for(int i = 0; i < MAX_ALARMS; i++){
		/*
		 * if the name match, replacing the location of the last alarm in the list with the current location,
		 * then deleting the last alarm.
		 */
		 if(strcmp(alarms[i].alarmName, name) == 0){
			alarms[i] = alarms[_cnt_alarms-1];
			memset(&alarms[_cnt_alarms-1], 0, sizeof(alarms[_cnt_alarms-1]));
			_cnt_alarms--;
			printf("deleted successfully\r\n");
			return;
		 }
	}
	printf("alarm not exist\r\n");
}

void AlarmManager_edit(char * name, int hour, int minutes, int stateRepeat)
{
	if(_cnt_alarms == 0){
		printf("there are no alarms");
		return;
	}
	for(int i = 0; i < MAX_ALARMS; i++){
		/*
		 * if the name match, setting all the parameters that received as the new values.
		 * all the parameters must be send.
		 */
		if(strcmp(alarms[i].alarmName, name) == 0){
			alarms[i].time = (hour * 3600) + (minutes * 60);
			alarms[i].isActive = ON;
			alarms[i].isOnRepeat = stateRepeat;
			alarms[i].alarmState = ALARM_STATE_OFF;
			alarms[i].cntTimerRing = 0;
			alarms[i].cntTimerWait = 0;
			alarms[i].cntSnooz = 0;
			printf("edited successfully\r\n");
			return;
		}
	}
	printf("alarm not exist\r\n");
}

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
	HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0, 1, readBuff, 7, 0Xff);
	for(int i = 0; i < _cnt_alarms; i++){
		if(alarms[i].isActive == 0){
			continue;
		}
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
		if(alarms[i].cntTimerRing >= 30){
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
			if(alarms[i].cntTimerWait >= 60){
				Buzzer_start(&buzzer);
				alarms[i].alarmState = ALARM_STATE_RINGING;
				alarms[i].cntTimerWait = 0;
			}
		}
	}
}

void AlarmManager_stopRing()
{
	for(int i = 0; i < _cnt_alarms; i++){
		if(alarms[i].alarmState == ALARM_STATE_RINGING){
			Buzzer_stop(&buzzer);
			alarms[i].alarmState = ALARM_STATE_OFF;
			if(alarms[i].isOnRepeat == OFF){
				AlarmManager_delete(alarms[i].alarmName);
			}
		}
	}
}

void AlarmManager_printAllAlarms()
{
	if(_cnt_alarms == 0){
		printf("help: no alarms\r\n");
		return;
	}
	for(int i = 0; i < _cnt_alarms; i++){
		printf("%d| alarmName:%s |timeInSec: %d \r\n",(i+1), alarms[i].alarmName ,alarms[i].time );
	}
}















