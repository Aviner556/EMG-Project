#ifndef _Buzzer_
#define _Buzzer_

#include <stdio.h>

typedef enum Buzz_State_
{
	STATE_MUSIC_ON,
	STATE_MUSIC_OFF,
}Buzz_State;

typedef struct Buzzer_
{
	Buzz_State state;
	size_t size;
	int currentNote;
	int tone;
	int maxCount;
	int counter;
}Buzzer;

void Buzzer_init(Buzzer * buzzer);
void Buzzer_start(Buzzer * buzzer);
void Buzzer_stop(Buzzer * buzzer);
void Buzzer_onTimerInterrupt(Buzzer * buzzer);
void Buzzer_playNote(Buzzer * buzzer);
void Buzzer_playNextNote(Buzzer * buzzer);


#endif
