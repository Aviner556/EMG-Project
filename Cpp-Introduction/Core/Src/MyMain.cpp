#include "MyMain.h"
#include "Led.h"
#include "Buttons.h"
#include "CliCommand.h"
#include "Communication.h"


extern UART_HandleTypeDef huart2;

LED blueLed;
Button blueButton;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

void CliCommand_init();

/*
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	blueLed.ledChangeState();
}
*/


extern "C" void mainloop() {

	CliCommand_init();

	while(1){

		if (Communication_commTask()){
			Communication_handleCommand();
		}

/*
		if(blueLed.ledGetState() == STATE_LED_OFF){
			blueLed.ledOn();
		}
		else if(blueLed.ledGetState() == STATE_LED_ON){
			blueLed.ledBlink();
		}
		else if(blueLed.ledGetState() == STATE_LED_BLINK){
			blueLed.ledOff();
		}
*/
	}
}

