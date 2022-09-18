#include "Communication.h"
#include "Led.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "cmsis_os.h" //include freeROTS

#define MAX_BUFFER_LENGTH 100

extern UART_HandleTypeDef huart2;
extern Led blueLed;
extern Led redLed;

extern osMessageQueueId_t myQueue01Handle;

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

static uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
static int _cmdcount = 0;
static int _cmdprint = 0;

int Communication_commTask()
{
	uint8_t ch;

		HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 0);
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
	char cmd1[25];
	char cmd2[25];
	  //uint32_t userCode;
	  char param[20];

	  int params = sscanf((const char*)_cmdbuffer, "%s %s %s", cmd1, cmd2, param);

	  if (params == 0)
	  {
		  return;
	  }
	  if(strcmp(cmd2, "delay") == 0){
		  if (strcmp(cmd1, "blueled") == 0){
			  blueLed.ledDelay = atoi(param);
			  return;
		  }
		  else if (strcmp(cmd1, "redled") == 0){
			  redLed.ledDelay = atoi(param);
			  return;
		  }
	  }
	  else if (strcmp(cmd1, "bright") == 0){
		  int bright = atoi(cmd2);
		  if(bright >= 0 && bright <= 10){
			  osMessageQueuePut(myQueue01Handle, &bright, 0, osWaitForever);
			  return;
		  }
		  printf("brightness most be 0-10\r\n\n");
		  return;
	  }

	  printf("invalid command\r\n");
}


/* USER CODE END Header_entry_UART */
void entry_UART(void *argument)
{
  /* USER CODE BEGIN entry_UART */
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







