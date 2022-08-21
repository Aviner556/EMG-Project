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
	ALARM_STATE_WAITING,
}alarmState;

typedef struct _Alarm
{
	char alarmName[10];
	int time;
	bool isActive;
	bool isOnRepeat;
	alarmState alarmState;
	int cntTimerRing;
	int cntTimerWait;
	int cntSnooz;
}Alarm;


void AlarmManager_init();
void AlarmManager_add(char * name, int hour, int minutes, int stateRepeat);
void AlarmManager_delete(char * name);
void AlarmManager_edit(char * name, int hour, int minutes, int stateRepeat);
void AlarmManager_onTimerIntterupt();
int AlarmManager_alarmIsOnTime();
void AlarmManager_ringOnTimerIntterupt();
void AlarmManager_ring(Alarm alarm);
void AlarmManager_stopRing();
void AlarmManager_printAllAlarms();

#endif
