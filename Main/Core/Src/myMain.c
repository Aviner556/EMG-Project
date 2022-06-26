#include "myMain.h"
#include "main.h"
#include "LED.h"
#include "buttons.h"
#include "buzzer.h"
#include "clock.h"

extern UART_HandleTypeDef huart2;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

LED blue;
LED red;
BUTTON B3;
BUTTON B2;
BUZZER buzzer;
CLOCK clc1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
	/////////// clock /////////////////////////////////////////////////////////////////
		workingTime(&clc1);

	/////////// led ///////////////////////////////////////////////////////////////////
		ledOnTimerInterrupt(&blue);
		ledOnTimerInterrupt(&red);

	/////////// buzzer ////////////////////////////////////////////////////////////////
		buzzerOnTimerInterrupt(&buzzer);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	///////////////////////////////////////////////////////////////////////////////////
	////buttons
	///////////////////////////////////////////////////////////////////////////////////
	if(GPIO_Pin == B2_Pin){
		buttonInterrupt(&B2);
	}
	else{
		if(blue.state == STATE_LED_OFF && red.state == STATE_LED_OFF){
			ledOn(&blue);
			ledOn(&red);
		}
		else{
			ledOff(&blue);
			ledOff(&red);
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	////buzzer
	///////////////////////////////////////////////////////////////////////////////////
	if(buzzer.state == STATE_MUSIC_OFF){
		HAL_TIM_Base_Start(&htim3);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		buzzer.state = STATE_MUSIC_ON;
		playNote(&buzzer);
	}
	else
	{
		HAL_TIM_Base_Stop(&htim3);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
		buzzer.state = STATE_MUSIC_OFF;
	}
}



void mainloop()
{
	ledInit(&blue,LD2_GPIO_Port, LD2_Pin);
	ledInit(&red,LD3_GPIO_Port, LD3_Pin);

	buttInit(&B2,B2_GPIO_Port,B2_Pin);
	buttInit(&B3,B3_GPIO_Port,B3_Pin);

	clockInit(&clc1);
	buzzerInit(&buzzer);

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	while(1){

	}
}
