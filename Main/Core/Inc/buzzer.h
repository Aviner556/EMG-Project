#ifndef _buzzer_
#define _buzzer_

#include <stdio.h>

typedef enum BUZZ_STATE_
{
	STATE_MUSIC_ON,
	STATE_MUSIC_OFF,
}BUZZ_STATE;

typedef struct BUZZER_
{
	BUZZ_STATE state;
	size_t size;
	int currentNote;
	int tone;
	int maxCount;
	int counter;
}BUZZER;

void buzzerInit(BUZZER *buzz);
void buzzerStart(BUZZER* buzzer);
void buzzerStop(BUZZER* buzzer);
void buzzerOnTimerInterrupt(BUZZER* buzz);
void playNote(BUZZER *buzz);
void playNextNote(BUZZER *buzz);


#endif
