#include "Flash.h"
#include "myMain.h"
#include "main.h"
#include <stdio.h>
#include <cstring>

#define MAGIC 0X5A5A
#define DATA_SIZE 18

FLASH_EraseInitTypeDef basicFlash;
extern TEMPLIMIT tempLim;


void Flash::read()
{
	HAL_FLASH_Unlock();
	TEMPLIMIT * data = (TEMPLIMIT *)_page_256_addr;
	if(data->magicNum != MAGIC){
		return;
	}
	tempLim = *data;
 }


void Flash::write(void * memory)
{
	// unlock the flash
	HAL_FLASH_Unlock();
	erase();

	uint64_t * Data = (uint64_t*)(memory);
	for(uint64_t i = 0; i <= DATA_SIZE; i++){
		_HAL_STATUS = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,_page_256_addr+(i*8),*(Data+i) );
		if(_HAL_STATUS != HAL_OK){
			printf("HAL_FLASH_Program not OK");
			return;
		}
	}
	HAL_FLASH_Lock();
}

void Flash::erase()
{
	uint32_t pageError;  // used without interrupt

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = _page_256_addr;
	basicFlash.NbPages = 1;

//	// unlock the flash
	HAL_FLASH_Unlock();

	// erase the page from the flash (interrupt)
	HAL_FLASHEx_Erase(&basicFlash, &pageError);

}



