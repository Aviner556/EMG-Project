#include "Flash.h"
#include "myMain.h"
#include "main.h"
#include <stdio.h>
#include <cstring>


FLASH_EraseInitTypeDef basicFlash;
extern TEMPLIMIT tempLim;


bool Flash::Flash_Read()
{
	HAL_FLASH_Unlock();
	TEMPLIMIT * data = (TEMPLIMIT *)_page_256_addr;
	memcpy(&tempLim, data, sizeof(TEMPLIMIT));
	if(tempLim.magicNum == 0X5A5A){
		return true;
	}
	return false;
}


void Flash::Flash_write(void * data)
{
	// unlock the flash
	HAL_FLASH_Unlock();
	Flash_erase();

	int size = sizeof(data);
	for(int i = 0; i < size; i += sizeof(uint64_t)){
		uint64_t Data = *(uint64_t *)(data+i);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)_page_256_addr+i,Data);
	}
}

void Flash::Flash_erase()
{
	uint32_t pageError;  // used without interrupt

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = (0x08080000);
	basicFlash.NbPages = 1;

//	// unlock the flash
	HAL_FLASH_Unlock();

	// erase the page from the flash (interrupt)
	HAL_FLASHEx_Erase(&basicFlash, &pageError);

}



