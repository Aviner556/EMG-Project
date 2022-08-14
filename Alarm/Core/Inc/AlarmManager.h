#ifndef INC_ALARMMANAGER_H_
#define INC_ALARMMANAGER_H_

typedef enum _bool
{
	OFF,
	ON,
}bool;

typedef struct _Alarm
{
	char alarmName[10];
	int time;
	bool isActive;
	bool isOnRepeat;
}Alarm;


void AlarmManager_init();
void AlarmManager_add(char * name, int hour, int minutes, bool stateRepeat);
void AlarmManager_delete(char * name);
void AlarmManager_edit(char * time, char * text, bool * stateRepeat);
void AlarmManager_onTimerIntterupt();
void AlarmManager_ring(Alarm alarm);

#endif
