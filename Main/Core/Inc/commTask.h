#ifndef _commTask_
#define _commTask_


int commTask();
void handleCommand();
void printHelp();
typedef void (*HandlerFunc)();

void registerCommand(char* commandName, HandlerFunc offFunc, void* obj);

typedef struct _COMMAND
{
	char* commandName;
	HandlerFunc commandPointer;
	void* obj;
}COMMAND;

#endif
