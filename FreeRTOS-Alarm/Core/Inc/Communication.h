#ifndef _Communication_
#define _Communication_

typedef void (* HandlerFunc)(void *);

typedef struct _Command
{
	char * commandName;
	HandlerFunc commandPointer;

}Command;

int Communication_commTask();
void Communication_handleCommand();
void RegisterCommand(char * commandName, HandlerFunc offFunc);

#endif
