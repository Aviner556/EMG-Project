#include "MyMain.h"
#include "Led.h"
#include "Led-PWM.h"
#include "Led-Gpio.h"
#include "Buttons.h"
#include "CliCommand.h"
#include "Communication.h"


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6; //1ms
extern TIM_HandleTypeDef htim2; //1ms PWM

LED * redLed = new LedGpio(LD3_GPIO_Port, LD3_Pin);
LED * blueLed = new LedPWM(&htim2, TIM_CHANNEL_1);

Button blueButton;

void CliCommand_init();

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	MainTimerIT_handleInterrupt();
}


extern "C" void mainloop() {

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	CliCommand_init();
	MainTimerIT_init();

	while(1){

		if (Communication_commTask()){
			Communication_handleCommand();
		}
	}
}


