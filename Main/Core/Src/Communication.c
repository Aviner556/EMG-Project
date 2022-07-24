#include "Communication.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANS_LENGTH 25

extern UART_HandleTypeDef huart2;

Command commands[MAX_COMMANS_LENGTH];
//char help[20][20];

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

static uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
static int _cnt_commands = 0;
static int _cmdcount = 0;
static int _cmdprint = 0;

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
		while (_cmdprint < _cmdcount)
		{
			HAL_UART_Transmit(&huart2, &_cmdbuffer[_cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch == '\r' || ch == '\n')
		{
			// here we have a time to print the command
			while (_cmdprint < _cmdcount)
			{
				HAL_UART_Transmit(&huart2, &_cmdbuffer[_cmdprint++], 1, 0xFFFF);
			}

			HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

			_cmdbuffer[_cmdcount] = 0;
			_cmdcount = 0;
			_cmdprint = 0;

			// command is ready
			return 1;
		}
	else if (ch == '\b')
		{
			char bs[] = "\b \b";
			_cmdcount--;
			_cmdprint--;
			HAL_UART_Transmit(&huart2, (uint8_t*)bs, strlen(bs), 0xFFFF);
		}
		else
		{
			if (_cmdcount >= MAX_BUFFER_LENGTH)
			{
				_cmdcount = 0;
				_cmdprint = 0;
			}

			_cmdbuffer[_cmdcount++] = ch;
		}
	return 0;
}



void Communication_handleCommand()
{
  char cmd[25];
  //uint32_t userCode;
  char param[20];

  int params = sscanf((const char*)_cmdbuffer, "%s %s", cmd, param);

  if (params == 0)
  {
	  return;
  }
  if(_cnt_commands != 0){
	  for(int i=0; i<_cnt_commands; i++){
	  	  if(strcmp(cmd, commands[i].commandName) == 0){
	  		  commands[i].commandPointer(commands[i].obj, param);
	  		  return;
	  	  }
	  }
  }
  else{
	  printf("0 commands\r\n");
	  return;
  }

  printf("Invalid command\r\n");

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
	for(int i = 0; i < _cnt_commands; i++){
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
	if(_cnt_commands < MAX_COMMANS_LENGTH){
		commands[_cnt_commands].commandName = commandName;
		commands[_cnt_commands].commandPointer = func;
		commands[_cnt_commands].obj = obj;
		_cnt_commands++;
	}
	else{
		printf("error\r\n");
	}
}
