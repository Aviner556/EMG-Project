#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdio.h>


typedef enum _FlashState
{
	STATE_INIT,
	STATE_ERASE,
	STATE_ERASE_END,
	STATE_PROGRAM,
	STATE_PROGRAM_END,
}FlashState;


class Flash
{
private:
	FlashState flashState;
	uint32_t* page_256_addr;
	int bufferSize;
	int bufferCnt;
	int lenght;
	uint8_t  flashBuffer[8];

public:
	Flash()
	{
		flashState = STATE_INIT;
		page_256_addr = (uint32_t *)(0x08080000);
		bufferSize = 8;
		bufferCnt = 0;
	}
	~Flash(){}

	void Flash_erase(Flash * flash);
	void Flash_write(Flash * flash);
};



#endif
