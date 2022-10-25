#include "AlarmManager.h"
#include "Clock.h"
#include "Buzzer.h"
#include "Flash.h"
#include <string.h>
#include <stdio.h>
#include "main.h"


#define MAX_ALARMS 5

extern Buzzer buzzer;
extern I2C_HandleTypeDef hi2c1;
extern Flash flashRW;
extern uint32_t* page_256_addr;

Alarm alarms[MAX_ALARMS];
static int _cnt_alarms = 0;
uint8_t readBuff[7];


void AlarmManager_initArray()
{
	memset(alarms, 0, sizeof(alarms));
	Alarm * pFlash = (Alarm *)page_256_addr;
	for(int i = 0; i < MAX_ALARMS; i++){
		alarms[i] = *(pFlash + i);
	}

}

void AlarmManager_initStruct(Alarm * alarm)
{
	strcpy(alarm->alarmName, "none");
	alarm->time = 0;
	alarm->isActive = 0;
	alarm->isOnRepeat = 0;
	alarm->alarmState = ALARM_STATE_OFF;
	alarm->cntTimerRing = 0;
	alarm->cntTimerWait = 0;
	alarm->cntSnooz = 0;
}

void AlarmManager_add(Alarm * alarm)
{
	// checking if there are free space for more alarms
	if(_cnt_alarms < MAX_ALARMS){
		strcpy(alarms[_cnt_alarms].alarmName, (char *)alarm->alarmName);
		alarms[_cnt_alarms].time = alarm->time;
		alarms[_cnt_alarms].isOnRepeat = alarm->isOnRepeat;
		alarms[_cnt_alarms].isActive = alarm->isActive;
		_cnt_alarms++;
		Flash_erase(&flashRW);
		Flash_write(&flashRW, &alarms, sizeof(Alarm)*MAX_ALARMS);
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
void AlarmManager_delete(Alarm * alarm)
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
		 if(strcmp(alarms[i].alarmName, alarm->alarmName) == 0){
			alarms[i] = alarms[_cnt_alarms-1];
			memset(&alarms[_cnt_alarms-1], 0, sizeof(alarms[_cnt_alarms-1]));
			_cnt_alarms--;
			printf("deleted successfully\r\n");
			return;
		 }
	}
	printf("alarm not exist\r\n");
}

void AlarmManager_edit(Alarm * alarm)
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
		if(strcmp(alarms[i].alarmName, alarm->alarmName) == 0){
			strcpy(alarms[_cnt_alarms].alarmName, (char *)alarm->alarmName);
			alarms[_cnt_alarms].time = alarm->time;
			alarms[_cnt_alarms].isOnRepeat = alarm->isOnRepeat;
			alarms[_cnt_alarms].isActive = alarm->isActive;
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
				AlarmManager_delete(&alarms[i]);
			}
		}
	}
}

void AlarmManager_printAllAlarms()
{
//	if(_cnt_alarms == 0){
//		printf("no alarms exist\r\n");
//		return;
//	}
	printf(" | alarmName    |timeInSec        |active\r\n");
	for(int i = 0; i < MAX_ALARMS; i++){
		printf("%d|%s            |%d       |%d\r\n",(i+1), alarms[i].alarmName ,alarms[i].time,alarms[i].isActive);
	}
}












