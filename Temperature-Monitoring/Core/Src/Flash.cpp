#include "Flash.h"
#include "myMain.h"
#include "main.h"
#include <stdio.h>
#include <cstring>


FLASH_EraseInitTypeDef basicFlash;
extern TEMPLIMIT tempLim;


void Flash::Flash_Read()
{
	HAL_FLASH_Unlock();
	TEMPLIMIT * data = (TEMPLIMIT *)_page_256_addr;
	if(data->magicNum != 0X5A5A){
		return;
	}
	tempLim = *data;
 }


void Flash::Flash_write(void * memory)
{
	// unlock the flash
	HAL_FLASH_Unlock();
	Flash_erase();

	uint64_t * Data = (uint64_t*)(memory);
	for(uint64_t i = 0; i <= 18; i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,_page_256_addr+(i*8),*(Data+i) );
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



