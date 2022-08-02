#include "MainTimerIT.h"
#include <string.h>
#include <stdio.h>

#define MAX_COMMANDS_IT_LENGTH 25

typedef struct _MainTimerIT
{
	TimerHandler funcPointer;
	void * obj;
	int isOn;
}MainTimerIT;

MainTimerIT commandsIT[MAX_COMMANDS_IT_LENGTH];
static int _cnt_commandsIT = 0;

void MainTimerIT_init(){
	memset(commandsIT, 0, sizeof(commandsIT));
}

void MainTimerIT_registerCallback(TimerHandler funcPointer, void * obj)
{
	for(int i = 0; i < MAX_COMMANDS_IT_LENGTH; i++){
		if(commandsIT[i].funcPointer == funcPointer && commandsIT[i].obj == obj){
			return;
		}
	}
	if(_cnt_commandsIT < MAX_COMMANDS_IT_LENGTH){
		commandsIT[_cnt_commandsIT].funcPointer = funcPointer;
		commandsIT[_cnt_commandsIT].obj = obj;
		commandsIT[_cnt_commandsIT].isOn = 1;
		_cnt_commandsIT++;
	}
}

void MainTimerIT_handleInterrupt()
{
	if(_cnt_commandsIT == 0){
		return;
	}
	for(int i = 0; i < _cnt_commandsIT; i++){
		if(commandsIT[i].isOn == 1){
			commandsIT[i].funcPointer(commandsIT[i].obj);
		}
		if(commandsIT[i].funcPointer == 0){
			return;
		}
	}
}

void MainTimerIT_registerCallbackRemove(TimerHandler funcPointer, void * obj)
{
	if(_cnt_commandsIT == 0){
		return;
	}
	for(int i = 0; i < MAX_COMMANDS_IT_LENGTH; i++){
		if(commandsIT[i].funcPointer == funcPointer && commandsIT[i].obj == obj){
			if(i == _cnt_commandsIT-1){
				memset(&commandsIT[i], 0, sizeof(commandsIT[i]));
				_cnt_commandsIT--;
				return;
			}
			else{
				commandsIT[i] = commandsIT[_cnt_commandsIT-1];
				memset(&_cnt_commandsIT-1, 0, sizeof(_cnt_commandsIT-1));
				_cnt_commandsIT--;
				//printf("removed from %d. last in %d\r\n",i,_cnt_commandsIT);
				return;
			}
		}
	}
}

