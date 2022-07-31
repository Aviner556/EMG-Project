#ifndef _Buzzer_
#define _Buzzer_

#include <stdio.h>

typedef enum BuzzState_
{
	STATE_MUSIC_ON,
	STATE_MUSIC_OFF,
}BuzzerState;

typedef struct Buzzer_
{
	BuzzerState state;
	size_t size;
	int currentNote;
	int tone;
	int maxCount;
	int counter;
}Buzzer;

void Buzzer_init(Buzzer * buzzer);
void Buzzer_start(Buzzer * buzzer);
void Buzzer_stop(Buzzer * buzzer);
void Buzzer_onTimerInterrupt(void * obj);
void Buzzer_playNote(Buzzer * buzzer);
void Buzzer_playNextNote(Buzzer * buzzer);


#endif
