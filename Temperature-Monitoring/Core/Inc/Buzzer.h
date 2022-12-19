#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdio.h>

enum BUTT_STATE
{
	STATE_MUSIC_ON,
	STATE_MUSIC_OFF,
	STATE_MUSIC_STOP
};

class Buzzer
{
private:
	int _notes[2] = {390, 202};
	int _currentNote;
	size_t _size;
	BUTT_STATE _state;

public:
	Buzzer(){
		_currentNote = 0;
		_size = sizeof(_notes)/sizeof(_notes[0]);
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
