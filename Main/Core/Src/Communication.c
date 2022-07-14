#include <Communication.h>
#include "stdio.h"
#include <main.h>
#include <string.h>

#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANS_LENGTH 25

extern UART_HandleTypeDef huart2;

Command commands[MAX_COMMANS_LENGTH];
//char help[20][20];

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cnt_commands = 0;
int cmdcount = 0;
int cmdprint = 0;

int Communication_commTask()
{
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch != '\r' && ch != '\n')
	{
		//HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}

	// here we have a time to print the command
	while (cmdprint < cmdcount)
	{
		HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}



void Communication_handleCommand()
{
  char cmd[25];
  //uint32_t userCode;
  char param[20];

  int params = sscanf((const char*)cmdbuffer, "%s %s", cmd, param);

  if (params == 0)
  {
	  return;
  }
  if(cnt_commands != 0){
	  for(int i=0; i<cnt_commands; i++){
	  	  if(strcmp(cmd, commands[i].commandName) == 0){
	  		  commands[i].commandPointer(commands[i].obj, param);
	  	  }
	  }
  }
  else
	  printf("0 commands\r\n");

  /*
  if (strcmp(cmd, "on") == 0)
  {
//	  if (_onFunc) {
//		  _onFunc(type);
//	  }
	  //setCode(userCode);
  }
  else if (strcmp(cmd, "off") == 0)
  {
//	  if (_offFunc) {
//	  	  _offFunc(type);
//	  }
  }
  else if (strcmp(cmd, "blink") == 0)
  {
//  	  if (_blinkFunc) {
//  	  	  _blinkFunc(type,100);
//  	  }
  }
  else
  {
	  printf("Invalid command\r\n");
  }
  */
}

void Communication_printHelp(){
	printf("available commands:\r\n");
	for(int i = 0; i < cnt_commands; i++){
		char* space;
		if(i > 8){
			space = " ";
		}
		else{
			space = "  ";
		}
		printf("%d%s-  %s\r\n", i+1, space, commands[i].commandName);
	}
	printf("\r\n");
}


void RegisterCommand(char* commandName, HandlerFunc func, void* obj)
{
	if(cnt_commands < MAX_COMMANS_LENGTH){
		commands[cnt_commands].commandName = commandName;
		commands[cnt_commands].commandPointer = func;
		commands[cnt_commands].obj = obj;
		cnt_commands++;
	}
	else{
		printf("error\r\n");
	}
}
