#ifndef _Communication_
#define _Communication_

typedef void (* HandlerFunc)(void *, char *);

typedef struct _Command
{
	char * commandName;
	HandlerFunc commandPointer;
	void * obj;
}Command;

int Communication_commTask();
void Communication_handleCommand();
void Communication_printHelp();

void RegisterCommand(char * commandName, HandlerFunc offFunc, void * obj);

#endif
