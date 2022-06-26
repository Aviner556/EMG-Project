#ifndef _buttons_
#define _buttons_
#include "main.h"

typedef enum BUTT_STATE_
{
	STATE_BUTT_UP,
	STATE_BUTT_DOWN,
}BUTT_STATE;

typedef struct _BUTTON
{
	BUTT_STATE butt_state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int tik;
}BUTTON;

void buttInit(BUTTON* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void buttonInterrupt(BUTTON* butt);

#endif
