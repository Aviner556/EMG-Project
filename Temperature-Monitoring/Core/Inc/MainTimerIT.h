#ifndef _MainTimerIT_
#define _MainTimerIT_

#include "TimerTask.h"

typedef struct _MainTimerIT
{
	TimerTask * timerTask;
	int isOn;
}MainTimerIT;

void MainTimerIT_init();
void MainTimerIT_registerCallback(TimerTask * timerTask);
void MainTimerIT_registerCallbackRemove(TimerTask * timerTask);
void MainTimerIT_handleInterrupt();



#endif
