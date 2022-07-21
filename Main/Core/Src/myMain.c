#include "Adc.h"
#include "MyMain.h"
#include "Led.h"
#include "Buttons.h"
#include "Buzzer.h"
#include "Clock.h"
#include "Cli.h"
#include "Communication.h"
#include "Dht11.h"
#include "main.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim16;
extern ADC_HandleTypeDef hadc2;

Led blue;
Led red;
Button B3; //red
Button B2; //blue
Buzzer buzzer;
Clock clc1;
Adc lightSensor;
Dht11 TempHum;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
	/////////// clock /////////////////////////////////////////////////////////////////
		Button_timeCnt(&B2);
		Clock_workingTime(&clc1);

	/////////// led ///////////////////////////////////////////////////////////////////
		Led_onTimerInterrupt(&blue);
		Led_onTimerInterrupt(&red);

		Led_brightness((lightSensor.value*10)/4095);
		//adcPrint(&hadc2);

	/////////// buzzer ////////////////////////////////////////////////////////////////
		Buzzer_onTimerInterrupt(&buzzer);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TempHum.gpioPin){
		Dht11_onGpioInterrupt(&TempHum, TempHum.gpioPin);
	}

	///////////////////////////////////////////////////////////////////////////////////
	////buttons
	///////////////////////////////////////////////////////////////////////////////////
//	if(GPIO_Pin == B2_Pin){
//		Button_interrupt(&B2);
//	}
//	else{
//		if(blue.state == STATE_LED_OFF && red.state == STATE_LED_OFF){
//			Led_on(&blue);
//			Led_on(&red);
//		}
//		else{
//			Led_off(&blue);
//			Led_off(&red);
//		}
//		Clock_showTime(&clc1);
//	}

	//ledBrightness(5);

	///////////////////////////////////////////////////////////////////////////////////
	////buzzer
	///////////////////////////////////////////////////////////////////////////////////
//	if(buzzer.state == STATE_MUSIC_OFF){
//		Buzzer_start(&buzzer);
//	}
//	else
//	{
//		Buzzer_stop(&buzzer);
//	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
//	if(hadc == &hadc1){
//		if(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK ){
//			potentiometer = HAL_ADC_GetValue(&hadc1);
//		}
//	}
	if(hadc == &hadc2){
		if(HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY) == HAL_OK ){
			lightSensor.value = HAL_ADC_GetValue(&hadc2);
		}
	}
}


void mainloop()
{
	Led_init(&blue,LD2_GPIO_Port, LD2_Pin);
	Led_init(&red,LD3_GPIO_Port, LD3_Pin);

	Button_init(&B2,B2_GPIO_Port,B2_Pin);
	Button_init(&B3,B3_GPIO_Port,B3_Pin);

	Clock_init(&clc1);
	Buzzer_init(&buzzer);

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);

	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
	HAL_ADC_Start_IT(&hadc2);

	Dht11_init(&TempHum);
	Dht11_Start(&TempHum);

	//RegisterCallbacks(ledOn,ledOff,&red);
	Cli_init();

	while(1){

		if (Communication_commTask()){
			Communication_handleCommand();
		}

	}
}
