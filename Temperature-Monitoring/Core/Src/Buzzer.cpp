#include "Buzzer.h"
#include "main.h"
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim3;
extern Buzzer * buzz;

/* USER CODE END Header_Entry_myMain */
extern "C" void Entry_Buzzer(void *argument)
{
  /* USER CODE BEGIN Entry_myMain */
  /* Infinite loop */
  for(;;)
  {
	  if(buzz->Buzzer_getState() == STATE_MUSIC_ON){
		  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
		  buzz->Buzzer_playNextNote();
		  osDelay(999);
	  }
    osDelay(1);
  }
  /* USER CODE END Entry_myMain */
}

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

void Buzzer::Buzzer_Stop(BUTT_STATE buttState)
{
	if(_state == STATE_MUSIC_ON || _state == STATE_MUSIC_STOP){
		HAL_TIM_Base_Stop_IT(&htim3);
		HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
		_state = buttState;
	}
}


void Buzzer::Buzzer_stateOn()
{
	if(_state == STATE_MUSIC_STOP){
		return;
	}
	_state =STATE_MUSIC_ON;
}

