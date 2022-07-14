#ifndef _Buttons_
#define _Buttons_
#include "main.h"

typedef enum Butt_State_
{
	STATE_NONE,
	STATE_PRESS,
	STATE_SHORT,
	STATE_LONG,
	STATE_DOUBLE,
}Button_State;

typedef struct _Button
{
	Button_State buttonState;
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	int tik;
	int countPress;
	int countTik;
}Button;

void Button_init(Button * button,GPIO_TypeDef * gpioPort, uint16_t gpioPin);
void Button_interrupt(Button * button);
void Button_decision(Button * button);
void Button_timeCnt(Button * button);
Button_State Button_checkState(Button * button);

#endif
