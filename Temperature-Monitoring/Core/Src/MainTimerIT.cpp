#include "MainTimerIT.h"
#include "TimerTask.h"
#include <string.h>
#include <stdio.h>

#define MAX_COMMANDS_IT_LENGTH 25

MainTimerIT commandsIT[MAX_COMMANDS_IT_LENGTH];
static int _cnt_commandsIT = 0;

void MainTimerIT_init(){
	memset(commandsIT, 0, sizeof(commandsIT));
}

void MainTimerIT_registerCallback(TimerTask * timerTask)
{
	// checking if the command not exist already.
	for(int i = 0; i < MAX_COMMANDS_IT_LENGTH; i++){
		if(commandsIT[i].timerTask == timerTask){
			return;
		}
	}
	// if there is free space for the commands, add it.
	if(_cnt_commandsIT < MAX_COMMANDS_IT_LENGTH){
		commandsIT[_cnt_commandsIT].timerTask = timerTask;
		commandsIT[_cnt_commandsIT].isOn = 1;
		_cnt_commandsIT++;
	}
}

void MainTimerIT_handleInterrupt()
{
	// if there is no commands - return.
	if(_cnt_commandsIT == 0){
		return;
	}

	for(int i = 0; i < _cnt_commandsIT; i++){
		if(commandsIT[i].isOn == 1){
			commandsIT[i].timerTask->timerFunc();
		}
		if(commandsIT[i].timerTask == 0){
			return;
		}
	}
}

void MainTimerIT_registerCallbackRemove(TimerTask * timerTask)
{
	if(_cnt_commandsIT == 0){
		return;
	}
	for(int i = 0; i < MAX_COMMANDS_IT_LENGTH; i++){
		if(commandsIT[i].timerTask == timerTask){
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

