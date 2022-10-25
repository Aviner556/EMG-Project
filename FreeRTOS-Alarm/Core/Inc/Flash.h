#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"

typedef enum _FlashState
{
	STATE_INIT,
	STATE_ERASE,
	STATE_ERASE_END,
	STATE_PROGRAM,
	STATE_PROGRAM_END,
}FlashState;

typedef struct _Flash
{
	FlashState flashState;
	int pageOffset;
	int writeCnt;
}Flash;


void Flash_init(Flash * flash);
void Flash_erase(Flash * flash);
void Flash_write(Flash * flash, void * data, uint32_t sizeOfData);
void Flash_Task(Flash * flash);

#endif
