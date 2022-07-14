#include <myMain.h>
#include <LED.h>

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

Led blue;
Led red;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){
		HAL_TIM_Base_Stop(&htim3);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	}
}



void mainloop()
{

	Led_init(&blue,LD2_GPIO_Port, LD2_Pin);
	Led_init(&red,LD3_GPIO_Port, LD3_Pin);

	printf("Enter the primary code:\r\n");

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);

	while(1)
	{
		if (Communication_commTask()){
			Communication_handleCommand();
		}
	}
}
