#include "Communication.h"
#include "AlarmManager.h"
#include "Clock.h"
#include "main.h"
#include "Cli.h"
#include <stdio.h>
#include <string.h>
#include "cmsis_os.h"

#define MAX_BUFFER_LENGTH 100
#define MAX_COMMANDS_LENGTH 25

extern UART_HandleTypeDef huart2;
extern uint8_t readBuff[7];
extern I2C_HandleTypeDef hi2c1;
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
  char cmd[25] = {0};
  int alarmHour = -1;
  int alarmMinutes = -1;
  int isOnRepeat = 0;
  int isActive = 0;
  Alarm alarm;
  AlarmManager_initStruct(&alarm);

  int params = sscanf((const char*)_cmdbuffer, "%s %s %d:%d %d %d", cmd, alarm.alarmName, &alarmHour, &alarmMinutes,
		                            &isActive ,&isOnRepeat);

  if (params == 0){
	  printf("param = 0\r\n");
	  return;
  }

  //checking if the time is valid
  if (strcmp(cmd, "add") == 0 || strcmp(cmd, "edit") == 0){
	  if(alarmHour>23|| alarmHour<0 || alarmMinutes>59 || alarmMinutes<0){
		  printf("Invalid time\r\n");
		  return;
	 }
  }

  // converting to seconds
  if(alarmHour == 0){
	  alarmHour = 24;
  }
  alarm.time = (alarmHour * 3600) + (alarmMinutes * 60);
  alarm.isActive = isActive;
  alarm.isOnRepeat = isOnRepeat;

  if(_cnt_commands != 0){
  	  for(int i=0; i<_cnt_commands; i++){
  	  	  if(strcmp(cmd, commands[i].commandName) == 0){
  	  		  commands[i].commandPointer(&alarm);
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

void RegisterCommand(char * commandName, HandlerFunc func)
{
	if(_cnt_commands < MAX_COMMANDS_LENGTH){
		commands[_cnt_commands].commandName = commandName;
		commands[_cnt_commands].commandPointer = func;
		_cnt_commands++;
	}
	else{
		printf("error\r\n");
	}
}


/* USER CODE END Header_entry_ComunicationTask */
void entry_ComunicationTask(void *argument)
{
  /* USER CODE BEGIN entry_ComunicationTask */
	Cli_init();
  /* Infinite loop */
  while(1)
  {
	  if (Communication_commTask()){
		  Communication_handleCommand();
	  }
	  osDelay(1);
  }
  /* USER CODE END entry_ComunicationTask */
}
