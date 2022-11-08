#include "MyMain.h"
#include "Led.h"
#include "Buttons.h"
#include "CliCommand.h"
#include "Communication.h"


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6; //1ms
extern TIM_HandleTypeDef htim4; //1ms PWM

LED blueLed;
Button blueButton;

void CliCommand_init();

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	MainTimerIT_handleInterrupt();
}


extern "C" void mainloop() {

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	CliCommand_init();
	MainTimerIT_init();

	while(1){

		if (Communication_commTask()){
			Communication_handleCommand();
		}
	}
}

