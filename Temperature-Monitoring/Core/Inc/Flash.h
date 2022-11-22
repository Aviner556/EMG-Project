#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdio.h>

class Flash
{
private:
	uint32_t* _page_256_addr;
	uint8_t _flashBuffer[8];
	int _pageOffset;

public:
	Flash()
	{
		_page_256_addr = (uint32_t *)(0x08080000);
		_pageOffset = 0;
	}
	~Flash(){}

	void Flash_write(void * data);
	void Flash_erase();
	bool Flash_Read();
};



#endif
