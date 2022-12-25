#ifndef _Communication_
#define _Communication_

#include "CliCommand.h"
//#include <stdint.h>

struct Command
{
	const char * commandName;
	CliCommand * command;
};


int Communication_commTask();
void Communication_handleCommand();
void Communication_printHelp();

void RegisterCommand(const char * commandName, CliCommand * command);




//#define MAX_COMMANDS_LENGTH 25
//#define MAX_BUFFER_LENGTH 100
//
//class Communication
//{
//private:
//	struct Command
//	{
//		const char * commandName;
//		CliCommand * command;
//	};
//
//	Command commands[MAX_COMMANDS_LENGTH];
//	uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
//	int _cnt_commands;
//	int _cmdcount;
//	int _cmdprint;
//
//public:
//	Communication()
//	{
//		_cnt_commands = 0;
//		_cmdcount = 0;
//		_cmdprint = 0;
//	};
//
//	int commTask();
//	void handleCommand();
//	void printHelp();
//
//	void RegisterCommand(const char * commandName, CliCommand * command);
//};

#endif

