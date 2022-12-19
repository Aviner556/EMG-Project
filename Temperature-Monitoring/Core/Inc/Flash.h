#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdio.h>
#include "main.h"

class Flash
{
private:
	HAL_StatusTypeDef _HAL_STATUS;
	uint32_t _page_256_addr;
	uint8_t _flashBuffer[8];
	int _pageOffset;

public:
	Flash()
	{
		_page_256_addr = 0x08080000UL;
		_pageOffset = 0;
	}
	~Flash(){}

	void write(void * data);
	void erase();
	void read();
};



#endif
