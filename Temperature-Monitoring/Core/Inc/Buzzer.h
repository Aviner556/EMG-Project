#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "TimerTask.h"
#include "MainTimerIT.h"
#include <stdio.h>

typedef enum BUTT_STATE_
{
	STATE_MUSIC_ON,
	STATE_MUSIC_OFF,
	STATE_MUSIC_STOP
}BUTT_STATE;

class Buzzer
{
private:
	int _note[2] = {390, 202};
	int _currentNote;
	size_t _size;
	BUTT_STATE _state;

public:
	Buzzer(){
		_currentNote = 0;
		_size = sizeof(_note)/sizeof(_note[0]);
		_state = STATE_MUSIC_OFF;
	}
	~Buzzer(){}

	void Buzzer_playNote(int noteIdx);
	void Buzzer_playNextNote();
	void Buzzer_Stop(BUTT_STATE buttState);
	void Buzzer_stateOn();
	BUTT_STATE Buzzer_getState()
	{
		return _state;
	}

};

#endif /* INC_BUZZER_H_ */
