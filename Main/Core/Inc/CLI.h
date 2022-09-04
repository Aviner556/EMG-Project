#ifndef _Cli_
#define _Cli_


void Cli_init();
void Cli_cmdLedOn(void * obj, char * param);
void Cli_cmdLedOff(void * obj, char * param);
void Cli_cmdLedBlink(void * obj, char * param);
void Cli_cmdBuzzerOn(void * obj, char * param);
void Cli_cmdBuzzerOff(void * obj, char * param);
void Cli_cmdFlashEraseWrite(void * obj, char * param);


#endif
