#include "buttons.h"
#include "main.h"
#include "LED.h"

int delayTik = 0;

void buttInit(BUTTON* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	butt->butt_state = STATE_NONE;
	butt->tikOn = 0;
	butt->tikOff = 0;
	butt->prevOff = 0;
	butt->countTik = 0;
	butt->GPIO_Pin = GPIO_Pin;
	butt->GPIOx = GPIOx;
}

void buttonInterrupt(BUTTON* butt)
{
	if(HAL_GPIO_ReadPin(butt->GPIOx, butt->GPIO_Pin) == 0){
		butt->tikOn = HAL_GetTick();
	}
	else if(HAL_GPIO_ReadPin(butt->GPIOx, butt->GPIO_Pin) == 1){
		butt->prevOff = butt->tikOff;
		butt->tikOff = HAL_GetTick();
	}
	if((butt->tikOff - butt->tikOn) > 500){
		butt->butt_state = STATE_LONG;
		printf("long\r\n");
	}
	else{
		if((butt->tikOn - butt->prevOff) <= 200){
			butt->butt_state = STATE_DOUBLE;
			printf("double\r\n");
		}
		else{
			butt->butt_state = STATE_SHORT;
			printf("short\r\n");
		}
	}
}

