#include "Communication.h"
#include "CliCommand.h"
#include "Rtc.h"
#include "Dht11.h"
#include "LED.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cmsis_os.h"

#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANDS_LENGTH 25

extern UART_HandleTypeDef huart2;

extern DateTime dateTime;

Command commands[MAX_COMMANDS_LENGTH];

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
  char param[20], param1[20], param2[20], param3[20], param4[20], param5[20];

  int params = sscanf((const char*)_cmdbuffer, "%s %s %s %s %s %s %s", cmd, param, param1, param2, param3, param4, param5);

  if (params == 0)
  {
	  return;
  }
  if(strcmp(cmd, "settime") == 0){
	  dateTime.day = atoi(param);
	  dateTime.month = atoi(param1);
	  dateTime.year = atoi(param2);
	  dateTime.weekDay = atoi(param3);
	  dateTime.hours = atoi(param4);
	  dateTime.min = atoi(param5);
	  dateTime.sec = 0;
  }
//  if(strcmp(cmd, "help") == 0){
//	  Communication_printHelp();
//	  return;
//  }
  else if(_cnt_commands != 0){
	  for(int i=0; i<_cnt_commands; i++){
	  	  if(strcmp(cmd, commands[i].commandName) == 0){
	  		  commands[i].command->doCommand(param);
	  		  return;
	  	  }
	  }
  }
  else{
	  printf("0 commands\r\n");
	  return;
  }

  printf("Invalid command\r\n");
}

void Communication_printHelp(){
	printf("available commands:\r\n");
	for(int i = 0; i < _cnt_commands; i++){
		const char* space;
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


void RegisterCommand(const char * commandName, CliCommand * command)
{
	if(_cnt_commands < MAX_COMMANDS_LENGTH){
		commands[_cnt_commands].commandName = commandName;
		commands[_cnt_commands].command = command;
		_cnt_commands++;
	}
	else{
		printf("error\r\n");
	}
}


/* USER CODE END Header_entry_UART */
extern "C" void Entry_UART(void *argument)
{
  /* USER CODE BEGIN entry_UART */

	CliCommand_init();
	Communication_printHelp();
  /* Infinite loop */
  for(;;)
  {
	if(Communication_commTask() == 1){
		Communication_handleCommand();
	}
    osDelay(1);
  }
  /* USER CODE END entry_UART */
}
