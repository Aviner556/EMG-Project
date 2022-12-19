#include "MyMain.h"
#include "main.h"
#include "LED.h"
#include "Buttons.h"
#include "Buzzer.h"
#include "Flash.h"
#include "CliCommand.h"
#include "Communication.h"
#include "SDCard.h"
#include "Rtc.h"
#include "Dht11.h"
#include <stdio.h>
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim6; // 1s
extern TIM_HandleTypeDef htim3; // pwm for buzzer
extern TIM_HandleTypeDef htim16; // 1us
extern I2C_HandleTypeDef hi2c1; // rtc
extern osMutexId_t SDC_MutexHandle; // Mutex for SD-Card

DateTime dateTime;
LOG logMSG;

DHT * dht = new DHT();
LED * led = new LED();
Buzzer * buzz = new Buzzer();
SDCARD * SDC = new SDCARD();
Rtc * rtc = new Rtc();
Flash * flash = new Flash();


TEMPLIMIT tempLim; //struct that holding the temperature limits
ALERT sysState = NORMAL_STATE; //system state



extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	buzz->Buzzer_Stop(STATE_MUSIC_STOP);
}


void createLog(char * bufferLog, LOG log){
	rtc->rtcGetTime(&dateTime);
	sprintf(bufferLog,"%02d/%02d/%02d Day-%d %02d:%02d:%02d	- severity: %s! - %s. temperature: %.2f%%\r\n",
			dateTime.day, dateTime.month, dateTime.year, dateTime.weekDay, dateTime.hours, dateTime.min,
			dateTime.sec, log.severity, log.message, dht->getTemp());
}


/* USER CODE END Header_Entry_myMain */
extern "C" void Entry_myMain(void *argument)
{
  /* USER CODE BEGIN Entry_myMain */
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);

	__HAL_TIM_SET_COUNTER(&htim3, 0);
	HAL_TIM_Base_Start(&htim3);

	flash->read();

	HAL_Delay(1000);//For SD Card

	char logName[8] = "log.txt";

  /* Infinite loop */
  for(;;)
  {
	  /************** NORMAL STATE **************/
	  if(dht->getTemp() < tempLim.warning){
		  if(sysState != NORMAL_STATE && dht->getTemp() < (tempLim.warning - 3)){
			  led->ledOff();
			  buzz->Buzzer_Stop(STATE_MUSIC_OFF);

			  osMutexAcquire(SDC_MutexHandle, osWaitForever);
			  	  strcpy(logMSG.severity,"NORMAL  ");
			  	  strcpy(logMSG.message,"returned to normal level");
			  	  createLog(SDC->getBufferLog(),logMSG);
			  	  SDC->writeSDLog(logName);
			  osMutexRelease(SDC_MutexHandle);

			  sysState = NORMAL_STATE;
		  }
		  else if(sysState == CRITICAL_STATE){
			  led->ledOff();
			  buzz->Buzzer_Stop(STATE_MUSIC_OFF);
		  }
	  }
	  /************** CRITICAL STATE **************/
	  else if(dht->getTemp() >= tempLim.critical){
		  if(sysState != CRITICAL_STATE){
			  led->ledBlink();
			  buzz->Buzzer_stateOn();

			  osMutexAcquire(SDC_MutexHandle, osWaitForever);
			  	  strcpy(logMSG.severity,"CRITICAL");
			  	  strcpy(logMSG.message,"reached critical level!");
			  	  createLog(SDC->getBufferLog(),logMSG);
			  	  SDC->writeSDLog(logName);
			  osMutexRelease(SDC_MutexHandle);

			  sysState = CRITICAL_STATE;
		  }
	  }
	  /************** WARNING STATE **************/
	  else if(dht->getTemp() >= tempLim.warning){
		  if(sysState == NORMAL_STATE){
			  led->ledOn();

			  osMutexAcquire(SDC_MutexHandle, osWaitForever);
			  	  strcpy(logMSG.severity,"WARNING");
			  	  strcpy(logMSG.message,"reached warning level");
			  	  createLog(SDC->getBufferLog(),logMSG);
			  	  SDC->writeSDLog(logName);
			  osMutexRelease(SDC_MutexHandle);

			  sysState = WARNING_STATE;
		  }
		  else if(sysState == CRITICAL_STATE && dht->getTemp() < (tempLim.critical - 3)){
			  led->ledOn();
			  buzz->Buzzer_Stop(STATE_MUSIC_OFF);

			  osMutexAcquire(SDC_MutexHandle, osWaitForever);
			  	  strcpy(logMSG.severity,"WARNING ");
			  	  strcpy(logMSG.message,"down to warning level");
			  	  createLog(SDC->getBufferLog(),logMSG);
			  	  SDC->writeSDLog(logName);
			  osMutexRelease(SDC_MutexHandle);

			  sysState = WARNING_STATE;
		  }
	  }
    osDelay(1);
  }
  /* USER CODE END Entry_myMain */
}

