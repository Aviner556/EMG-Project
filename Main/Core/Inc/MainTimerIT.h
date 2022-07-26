#ifndef _MainTimerIT_
#define _MainTimerIT_

typedef void (* TimerHandler)(void *, void *);

typedef struct _MainTimerIT
{
	TimerHandler funcPointer;
	void * obj;
}MainTimerIT;





#endif
