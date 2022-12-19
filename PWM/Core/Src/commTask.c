#include "commTask.h"
#include "LED.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

#define MAX_BUFFER_LENGTH 100

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
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
  char cmd[20];
  int userBright;

  int params = sscanf((const char*)cmdbuffer, "%s %d", cmd, &userBright);

  if (params == 0)
  {
	  return;
  }

//  if (strcmp(cmd, "start") == 0)
//  {
//	  ledStart(maxCount);
//  }
//  else if (strcmp(cmd, "stop") == 0)
//  {
//	  ledStop();
//  }
  if (strcmp(cmd, "full") == 0)
    {
  	  start();
    }
  else if (strcmp(cmd, "off") == 0)
    {
  	  stop();
    }
//  else if (strcmp(cmd, "blink") == 0)
//    {
//	  flashing();
//    }
//  else if (strcmp(cmd, "half") == 0)
//    {
//	  DIM();
//    }
  else if (strcmp(cmd, "bright") == 0)
      {
	  	  setBrightness(userBright);
      }
  else
  {
	  printf("Invalid command\r\n");
  }
}
