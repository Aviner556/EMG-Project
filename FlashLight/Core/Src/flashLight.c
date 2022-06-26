#include "flashLight.h"

FlashLightState currentState = STATE_OFF;
void LEDcontrol();

FlashLightState changeState()
{
	switch(currentState)
	{
	case STATE_OFF:
		currentState = STATE_ON;
		break;
	case STATE_ON:
		currentState = STATE_DIM;
		break;
	case STATE_DIM:
		currentState = STATE_FLASHING;
		break;
	case STATE_FLASHING:
		currentState = STATE_OFF;
		break;
	default:
		currentState = STATE_OFF;
		break;
	}
	LEDcontrol();
	return currentState;
}
