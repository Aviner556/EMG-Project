#ifndef INC_ALARMMANAGER_H_
#define INC_ALARMMANAGER_H_

typedef enum _bool
{
	OFF,
	ON,
}bool;

typedef enum _alarmState
{
	ALARM_STATE_OFF,
	ALARM_STATE_RINGING,
	ALARM_STATE_WAITING, // between rings
}alarmState;

typedef struct _Alarm
{
	char alarmName[10];
	int time; // when it needs to ring, in seconds from the start of this day
	bool isActive; // off = 0; on = 1;
	bool isOnRepeat;
	alarmState alarmState;
	int cntTimerRing; // how long it's ringing
	int cntTimerWait;
	int cntSnooz; // how many time it will ring
}Alarm;


void AlarmManager_initArray();
void AlarmManager_initStruct(Alarm * alarm);
void AlarmManager_add(Alarm * alarm);
void AlarmManager_delete(Alarm * alarm);
void AlarmManager_edit(Alarm * alarm);
void AlarmManager_onTimerIntterupt();
int AlarmManager_alarmIsOnTime();
void AlarmManager_ringOnTimerIntterupt();
void AlarmManager_ring(Alarm * alarm);
void AlarmManager_stopRing();
void AlarmManager_printAllAlarms();

#endif
