#ifndef _Communication_
#define _Communication_


int Communication_commTask();
void Communication_handleCommand();
void Communication_printHelp();
typedef void (* HandlerFunc)(void *, char *);

void RegisterCommand(char * commandName, HandlerFunc offFunc, void * obj);

typedef struct _Command
{
	char * commandName;
	HandlerFunc commandPointer;
	void * obj;
}Command;

#endif
