/*
 * MyMain.cpp
 *
 *  Created on: 11 בדצמ׳ 2022
 *      Author: Aviner
 */

#include "main.h"
#include "ADC.h"
#include "Dht11.h"
#include "ADC-Potentiometer.h"
#include "ADC-LightSensor.h"
#include <stdio.h>

extern ADC_HandleTypeDef hadc1;  // ADC potentiometer
extern ADC_HandleTypeDef hadc2;  // ADC light sensor
extern TIM_HandleTypeDef htim6;  // 1ms
extern TIM_HandleTypeDef htim16; // 1us for DHT
extern TIM_HandleTypeDef htim3;  // PWM for buzzer
extern UART_HandleTypeDef huart2;


ADC * adcP = new AdcPotentiometer();
ADC * adcL = new AdcLightSensor();
DHT * dht = new DHT();


int cnt = 0;

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	cnt++;
	if(cnt >= 950 && cnt < 1000){
		HAL_ADC_Start_IT(&hadc1);
		HAL_ADC_Start_IT(&hadc2);
	}
	else if(cnt >= 1000){
		cnt = 0;
		printf("potentiometer = %lu\r\n",adcP->getValue());
		printf("light sensor = %lu\r\n\r\n",adcL->getValue());
	}
}


extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	AdcInterrupt(hadc, adcP, adcL);
}


extern "C" void mainloop()
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	__HAL_TIM_SET_COUNTER(&htim16, 0);
	HAL_TIM_Base_Start(&htim16);

	__HAL_TIM_SET_COUNTER(&htim3, 0);
	HAL_TIM_Base_Start_IT(&htim3);

	while(1){

	};

}
