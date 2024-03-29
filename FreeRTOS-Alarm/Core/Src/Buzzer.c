#include "Buzzer.h"


extern TIM_HandleTypeDef htim3;

static int _note[] = {390, 340, 303, 286, 255, 227, 202};
static int _length[] = {300, 300, 300, 300, 300, 300, 500};

void Buzzer_init(Buzzer * buzz)
{
	buzz->state = STATE_MUSIC_OFF;
	buzz->size = sizeof(_note)/sizeof(_note[0]);
	buzz->counter = 0;
	buzz->currentNote = 0;
	buzz->maxCount = _length[0];
	buzz->tone = 1;
}

void Buzzer_start(Buzzer * buzzer)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	buzzer->state = STATE_MUSIC_ON;
	//MainTimerIT_registerCallback(Buzzer_onTimerInterrupt, buzzer);
	Buzzer_playNote(buzzer);
}

void Buzzer_stop(Buzzer * buzzer)
{
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	buzzer->state = STATE_MUSIC_OFF;
	//MainTimerIT_registerCallbackRemove(Buzzer_onTimerInterrupt, buzzer);
}

void Buzzer_playNote(Buzzer * buzz)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, _note[buzz ->currentNote]);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (_note[buzz ->currentNote])/2);
}

void Buzzer_playNextNote(Buzzer * buzz)
{
	buzz->currentNote++;
	if(buzz->currentNote >= buzz ->size){
		buzz->currentNote = 0;
	}
	buzz->maxCount = _length[buzz ->currentNote];

	Buzzer_playNote(buzz);
}

void Buzzer_onTimerInterrupt(void * obj)
{
	Buzzer * buzz = (Buzzer *)obj;
	if(buzz->state == STATE_MUSIC_ON){
		buzz->counter++;
		if(buzz->counter >= buzz ->maxCount){
			Buzzer_playNextNote(buzz);
			buzz->counter = 0;
		}
	}
}

