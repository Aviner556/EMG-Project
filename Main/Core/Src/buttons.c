#include "buttons.h"
#include "main.h"
#include "LED.h"

extern BUTTON B2;

int delayTik = 0;

void buttInit(BUTTON* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	butt->butt_state = STATE_NONE;
	butt->tik = 0;
	butt->countPress = 0;
	butt->countTik = 0;
	butt->GPIO_Pin = GPIO_Pin;
	butt->GPIOx = GPIOx;
}

void buttonInterrupt(BUTTON* butt)
{
	if(HAL_GPIO_ReadPin(butt->GPIOx, butt->GPIO_Pin) == 0){
		butt->tik = HAL_GetTick();
		butt->countPress++;
	}
	else if(HAL_GPIO_ReadPin(butt->GPIOx, butt->GPIO_Pin) == 1){
		butt->butt_state = STATE_PRESS;
		if((HAL_GetTick() - butt->tik) > 500){
			butt->butt_state = STATE_LONG;
			butt->countPress = 0;
			butt->countTik = 0;
			printf("long\r\n");
		}
	}
}

void buttonDecision(BUTTON* butt)
{
	if(butt->countPress >= 2){
		butt->butt_state = STATE_DOUBLE;
		printf("double\r\n");
	}
	else if(butt->countTik > 200){
		butt->butt_state = STATE_SHORT;
		printf("short\r\n");
	}
	butt->countPress = 0;
	butt->countTik = 0;
}

void buttTimeCnt(BUTTON* butt)
{
	if(B2.butt_state == STATE_PRESS){
		butt->countTik++;
		if(butt->countTik > 200){
			buttonDecision(butt);
		}
	}
}

BUTT_STATE Button_checkState(BUTTON* butt)
{
	return butt->butt_state;
}
