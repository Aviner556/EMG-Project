#ifndef _buttons_
#define _buttons_
#include "main.h"

typedef enum BUTT_STATE_
{
	STATE_NONE,
	STATE_SHORT,
	STATE_LONG,
	STATE_DOUBLE,
}BUTT_STATE;

typedef struct _BUTTON
{
	BUTT_STATE butt_state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int tikOn;
	int tikOff;
	int prevOff;
	int countTik;
}BUTTON;

void buttInit(BUTTON* butt,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void buttonInterrupt(BUTTON* butt);

#endif
