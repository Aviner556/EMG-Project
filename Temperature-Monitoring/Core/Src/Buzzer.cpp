#include "Buzzer.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

void Buzzer::Buzzer_playNote(int noteIdx)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, _note[noteIdx]);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (_note[noteIdx])/2);
}

void Buzzer::Buzzer_playNextNote()
{
	_currentNote++;
	if(_currentNote >= (int)_size){
		_currentNote = 0;
	}
	Buzzer_playNote(_currentNote);
}

void Buzzer::Buzzer_Stop()
{
	if(_state == STATE_MUSIC_ON){
		HAL_TIM_Base_Stop_IT(&htim3);
		HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
		_state = STATE_MUSIC_OFF;
	}
}

void Buzzer::timerFunc()
{
	if(_state == STATE_MUSIC_ON){
		HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
		Buzzer_playNextNote();
	}
}
