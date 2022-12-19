#ifndef _Communication_
#define _Communication_

#include "CliCommand.h"


struct Command
{
	const char * commandName;
	CliCommand * command;
};


int Communication_commTask();
void Communication_handleCommand();
void Communication_printHelp();

void RegisterCommand(const char * commandName, CliCommand * command);

#endif

