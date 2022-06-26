#include "buttons.h"
#include "main.h"
#include "LED.h"

extern LED red;
extern LED blue;

void buttInit(BUTTON* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	butt ->butt_state = STATE_BUTT_UP;
	butt ->tik = 0;
	butt ->GPIO_Pin = GPIO_Pin;
	butt ->GPIOx = GPIOx;
}

void buttonInterrupt(BUTTON* butt)
{
	if(butt ->butt_state == STATE_BUTT_UP){
		butt ->butt_state = STATE_BUTT_DOWN;
		butt ->tik = HAL_GetTick();
	}
	else{
		butt ->butt_state = STATE_BUTT_UP;
		if(HAL_GetTick() - butt ->tik < 500){
			ledOff(&red);
			ledBlink(&blue,500);
		}
		else{
			ledOff(&blue);
			ledBlink(&red, 500);
		}
	}
}
