#include "Buttons.h"
#include "main.h"
#include "LED.h"


/*
extern Led red;
extern Led blue;

void Button_init(Button* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	butt ->butt_state = STATE_BUTT_UP;
	butt ->tik = 0;
	butt ->GPIO_Pin = GPIO_Pin;
	butt ->GPIOx = GPIOx;
}

void Button_interrupt(Button* butt)
{
	if(butt ->butt_state == STATE_BUTT_UP){
		butt ->butt_state = STATE_BUTT_DOWN;
		butt ->tik = HAL_GetTick();
	}
	else{
		butt ->butt_state = STATE_BUTT_UP;
		if(HAL_GetTick() - butt ->tik < 500){
			Led_off(&red);
			Led_blink(&blue,500);
		}
		else{
			Led_off(&blue);
			Led_blink(&red, 500);
		}
	}
}

*/
