#include <commTask.h>
#include "stdio.h"
#include <main.h>

#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANS_LENGTH 20

extern UART_HandleTypeDef huart2;

COMMAND commands[MAX_COMMANS_LENGTH];

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int CNT_COMMANDS = 0;
int cmdcount = 0;
int cmdprint = 0;

int commTask()
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



void handleCommand()
{
  char cmd[25];
  uint32_t userCode;

  int params = sscanf((const char*)cmdbuffer, "%s %lu", cmd, &userCode);

  if (params == 0)
  {
	  return;
  }

  for(int i=0; i<CNT_COMMANDS; i++){
	  if(strcmp(cmd, commands[i].commandName) == 0){
		  commands[i].commandPointer(commands[i].obj);
	  }
  }
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


void registerCommand(char* commandName, HandlerFunc func, void* obj)
{
	if(CNT_COMMANDS < MAX_COMMANS_LENGTH){
		commands[CNT_COMMANDS].commandName = commandName;
		commands[CNT_COMMANDS].commandPointer = func;
		commands[CNT_COMMANDS].obj = obj;
		CNT_COMMANDS++;
	}
	else{
		printf("error\r\n");
	}
}

