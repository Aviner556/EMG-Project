#include "LinkedList.h"
#include <stdio.h>
#include "cmsis_os.h"
#include "main.h"

extern LinkedList myList;

void LOGOUTPUT(TYPE type, char * message,...)
{
	LinkedList_addBegin(&myList, type, message);
}



/* USER CODE END Header_entry_myTask01 */
void entry_myTask01(void *argument)
{
  /* USER CODE BEGIN entry_myTask01 */
	char buffer[80];
  /* Infinite loop */
  for(;;)
  {
    osDelay(500);
    sprintf(buffer, "TASK-01 %lu", HAL_GetTick());
    LOGOUTPUT(TYPE_DEBUG, buffer);
  }
  /* USER CODE END entry_myTask01 */
}



/* USER CODE END Header_entry_myTask02 */
void entry_myTask02(void *argument)
{
  /* USER CODE BEGIN entry_myTask02 */
	char buffer[80];
  /* Infinite loop */
  for(;;)
  {
	  osDelay(300);
	  sprintf(buffer, "TASK-02 %lu", HAL_GetTick());
	  LOGOUTPUT(TYPE_ERROR, buffer);
  }
  /* USER CODE END entry_myTask02 */
}



/* USER CODE END Header_entry_Logger */
void entry_Logger(void *argument)
{
  /* USER CODE BEGIN entry_Logger */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    LinkedList_printAndDelete(&myList);
  }
  /* USER CODE END entry_Logger */
}
