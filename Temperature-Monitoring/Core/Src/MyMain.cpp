#include "main.h"
#include "MyMain.h"
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

DateTime dateTime;
DHT * dht = new DHT();
LED * led = new LED();
Buzzer * buzz = new Buzzer();
SDCARD * SDC = new SDCARD();
Rtc * rtc = new Rtc();
Flash * flash = new Flash();


TEMPLIMIT tempLim;
ALERT sysState = NORMAL_STATE;

static char bufferLog[50];


extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	buzz->Buzzer_Stop(STATE_MUSIC_STOP);
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
	HAL_TIM_Base_Start_IT(&htim3);

	flash->Flash_Read();

	HAL_Delay(1000);//For SD Card

  /* Infinite loop */
  for(;;)
  {
	  if(dht->Dht11_getTemp() < (tempLim.warning - 3)){
		  if(sysState != NORMAL_STATE){
			  led->ledOff();
			  buzz->Buzzer_Stop(STATE_MUSIC_OFF);
			  sysState = NORMAL_STATE;
		  }
	  }
	  else if(dht->Dht11_getTemp() >= tempLim.critical){
		  if(sysState != CRITICAL_STATE){
			  led->ledBlink();
			  buzz->Buzzer_stateOn();
			  rtc->rtcGetTime(&dateTime);
			  sprintf(bufferLog,"%d/%d/%d %d %d:%d:%d - critical temperature! %.2f\r\n",dateTime.day,dateTime.month,
					  dateTime.year,dateTime.weekDay,dateTime.hours,dateTime.min,dateTime.sec,dht->Dht11_getTemp());
			  SDC->writeSDLog(bufferLog);
			  sysState = CRITICAL_STATE;
		  }
	  }
	  else if(dht->Dht11_getTemp() >= tempLim.warning){
		  if(sysState == NORMAL_STATE){
			  led->ledOn();
			  sysState = WARNING_STATE;
		  }
		  else if(sysState == CRITICAL_STATE && dht->Dht11_getTemp() < (tempLim.critical - 3)){
			  led->ledOn();
			  buzz->Buzzer_Stop(STATE_MUSIC_OFF);
			  sysState = WARNING_STATE;
		  }
	  }
    osDelay(1);
  }
  /* USER CODE END Entry_myMain */
}

