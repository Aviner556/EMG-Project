#include "main.h"
#include "Buttons.h"
#include <stdio.h>

extern Button B2;

//static int delayTik = 0; //unused

void Button_init(Button * button,GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin)
{
	button->buttonState = STATE_NONE;
	button->tik = 0;
	button->countPress = 0;
	button->countTik = 0;
	button->gpioPin = GPIO_Pin;
	button->gpioPort = GPIOx;
}

void Button_interrupt(Button* button)
{
	// checking if the button pressed and counting
	if(HAL_GPIO_ReadPin(button->gpioPort, button->gpioPin) == 0){
		button->tik = HAL_GetTick();
		button->countPress++;
	}
	else if(HAL_GPIO_ReadPin(button->gpioPort, button->gpioPin) == 1){
		button->buttonState = STATE_PRESS;
		if((HAL_GetTick() - button->tik) > 500){
			button->buttonState = STATE_LONG;
			button->countPress = 0;
			button->countTik = 0;
			//printf("long\r\n");
		}
	}
}

void Button_timeCnt(Button* butt)
{
	if(B2.buttonState == STATE_PRESS){
		butt->countTik++;
		if(butt->countTik > 200){
			Button_decision(butt);
		}
	}
}

void Button_decision(Button* button)
{
	if(button->countPress >= 2){
		button->buttonState = STATE_DOUBLE;
		printf("double\r\n");
	}
	else if(button->countTik > 200){
		button->buttonState = STATE_SHORT;
		printf("short\r\n");
	}
	button->countPress = 0;
	button->countTik = 0;
}
