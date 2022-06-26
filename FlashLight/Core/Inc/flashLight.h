#ifndef _FLASH_LIGHT_H_
#define _FLASH_LIGHT_H_

typedef enum FlashLightState_
{
	STATE_OFF,
	STATE_ON,
	STATE_DIM,
	STATE_FLASHING
}FlashLightState;

extern FlashLightState currentState;
FlashLightState changeState();

#endif
