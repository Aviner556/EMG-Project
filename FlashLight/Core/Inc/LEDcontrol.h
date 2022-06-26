#ifndef _LED_CONTROL_H_
#define _LED_CONTROL_H_

void start();
void stop();
void DIM();
void flashing();
void setBrightness(int brightness);

extern int brightLevel;
extern int brightCnt;

#endif
