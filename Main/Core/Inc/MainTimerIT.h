#ifndef _MainTimerIT_
#define _MainTimerIT_


typedef void (* TimerHandler)(void *);

void MainTimerIT_init();
void MainTimerIT_registerCallback(TimerHandler funcPointer, void * obj);
void MainTimerIT_registerCallbackRemove(TimerHandler funcPointer, void * obj);
void MainTimerIT_handleInterrupt();



#endif
