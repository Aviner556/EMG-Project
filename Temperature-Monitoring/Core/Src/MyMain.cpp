#include "main.h"
#include "LED.h"
#include "Buttons.h"
#include "Buzzer.h"
#include "MyMain.h"
#include "Flash.h"
#include "CliCommand.h"
#include "Communication.h"
#include "MainTimerIT.h"
#include "Rtc.h"
#include "Dht11.h"
#include <stdio.h>
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim6; // 1s
extern TIM_HandleTypeDef htim3; // pwm for buzzer
extern TIM_HandleTypeDef htim16; // 1us
extern I2C_HandleTypeDef hi2c1; // rtc

DHT * dht = new DHT();
LED * led = new LED();
Buzzer * buzz = new Buzzer();
TEMPLIMIT tempLim;


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
  /* Infinite loop */
  for(;;)
  {
	  if(dht->Dht11_getTemp() >= tempLim.critical){
		  led->ledBlink();
		  buzz->Buzzer_stateOn();
	  }
	  else if(dht->Dht11_getTemp() >= tempLim.warning){
		  led->ledOn();
	  }
	  if(dht->Dht11_getTemp() < (tempLim.warning - 3)){
		  led->ledOff();
		  buzz->Buzzer_Stop(STATE_MUSIC_OFF);
	  }
	  else if(dht->Dht11_getTemp() < (tempLim.critical - 3)){
		  led->ledOn();
		  buzz->Buzzer_Stop(STATE_MUSIC_OFF);
	  }
    osDelay(1);
  }
  /* USER CODE END Entry_myMain */
}


/*
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6; // 1s
extern TIM_HandleTypeDef htim3; // pwm for buzzer
extern TIM_HandleTypeDef htim16; // 1us
extern I2C_HandleTypeDef hi2c1; // rtc

DateTime time;
DHT * dht = new DHT();
Rtc * rtc = new Rtc();
LED * led = new LED();
Buzzer * buzz = new Buzzer();
Flash * flash = new Flash();





extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
		MainTimerIT_handleInterrupt();
		flash->Flash_Read();
	}
}


extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	buzz->Buzzer_Stop();
}


extern "C" void mainloop()
{
	CliCommand_init();

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);

	__HAL_TIM_SET_COUNTER(&htim3, 0);
	HAL_TIM_Base_Start_IT(&htim3);

	flash->Flash_write();

	while(1){
		if (Communication_commTask()){
			Communication_handleCommand();
		}
		if(dht->Dht11_getTemp() > 45){
			led->ledBlink();
			buzz->Buzzer_stateOn();
		}
		else if(dht->Dht11_getTemp() < 40){
			led->ledOff();
			buzz->Buzzer_Stop();
		}
	}
}
*/
