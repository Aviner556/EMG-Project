#include "SDCard.h"
#include "Dht11.h"
#include "Rtc.h"
#include <stdio.h>
#include "cmsis_os.h"

extern osMutexId_t SDC_MutexHandle;

extern DateTime dateTime;

extern SDCARD * SDC;
extern Rtc * rtc;
extern DHT * dht;



/* USER CODE END Header_Entry_temperature */
extern "C" void Entry_temperature(void *argument)
{
  /* USER CODE BEGIN Entry_temperature */
	char logName[9] = "temp.txt";
  /* Infinite loop */
  for(;;)
  {
	  osDelay(59800);

	  osMutexAcquire(SDC_MutexHandle, osWaitForever);
	  	  rtc->rtcGetTime(&dateTime);
	  	  sprintf(SDC->getBufferLog(),"%02d/%02d/%02d Day-%d %02d:%02d:%02d - Temperature: %.2f%%\r\n",dateTime.day,dateTime.month,
	  			  dateTime.year,dateTime.weekDay,dateTime.hours,dateTime.min,dateTime.sec,dht->Dht11_getTemp());
	  	  SDC->writeSDLog(logName);
	  osMutexRelease(SDC_MutexHandle);
  }
  /* USER CODE END Entry_temperature */
}
