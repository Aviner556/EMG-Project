#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdio.h>
#include "main.h"

#define FLASH_START_ADDRESS 0x08000000
#define PAGE_SIZE 			2048

class Flash
{
private:
	HAL_StatusTypeDef _HAL_STATUS_FLASH;
	uint32_t _address;
	uint32_t _page;
	uint32_t flashStartAddess;
	uint8_t _flashBuffer[8];
	int _pageOffset;

public:
	Flash()
	{
		flashStartAddess = FLASH_START_ADDRESS;
		_address = 0x08080000UL;
		_page = (_address - flashStartAddess)/PAGE_SIZE;
		_pageOffset = 0;
	}
	~Flash(){}

	void write(void * data);
	void erase();
	void read();
};



#endif
