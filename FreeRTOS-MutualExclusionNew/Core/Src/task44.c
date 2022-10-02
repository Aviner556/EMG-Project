#include <stdio.h>
#include <string.h>
#include <task44.h>
#include "cmsis_os.h"
#include "main.h"

//#define USE_MUTEX
#define USE_CRIT_SEC

extern osMutexId_t myMutex01Handle;
static int GLOBAL = 0;

void printTask(char* name)
{
	printf("Hi! My name is %s!\r\n\n",name);
}


void syncStart(){
	#if defined(USE_MUTEX)
	  osMutexAcquire(myMutex01Handle, osWaitForever);
	#elif defined(USE_CRIT_SEC)
	  int checkG = 1;
	  while(checkG == 1){
		  taskENTER_CRITICAL();
		  checkG = GLOBAL;
		  if(checkG == 0){
			  GLOBAL = 1;
		  }
		  taskEXIT_CRITICAL();
	  }
	#endif
}

void syncEnd(){
	#if defined(USE_MUTEX)
		osMutexRelease(myMutex01Handle);
	#elif defined(USE_CRIT_SEC)
		GLOBAL = 0;
	#endif
}


/* USER CODE END Header_entry_Task01 */
void entry_Task(void *argument)
{
  /* USER CODE BEGIN entry_Task01 */

	PrintTask44 * task = (PrintTask44*)argument;

  /* Infinite loop */
  for(;;)
  {
	  syncStart();
	  for(int i = 0; i < 3; i++){
		  printTask(task->buff);
		  osDelay(task->delay);
	  }
	  syncEnd();
	  osDelay(1);
  }
  //osThreadTerminate(osThreadGetId());
  /* USER CODE END entry_Task01 */
}


