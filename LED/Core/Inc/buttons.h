#ifndef _buttons_
#define _buttons_
#include "main.h"

typedef enum BUTT_STATE_
{
	STATE_BUTT_UP,
	STATE_BUTT_DOWN,
}Button_State;

typedef struct _BUTTON
{
	Button_State butt_state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int tik;
}Button;

void Button_init(Button* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Button_interrupt(Button* butt);

#endif
