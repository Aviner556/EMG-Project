#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "Dht11.h"

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
	int currentPage;
	int pageOffset;
	int writeCnt;
	int bufferSize;
	int bufferCnt;
	int lenght;

	// the value that need to be save on the flash
	uint8_t  flashBuffer[8];
}Flash;


void Flash_init(Flash * flash);
void Flash_locPage(Flash * flash);
void Flash_erase(Flash * flash);
void Flash_write(Flash * flash);
//void Flash_write(Flash * flash, void * buffer, int lenght);
void Flash_Task(Flash * flash);

#endif
