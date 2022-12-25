#include "Flash.h"
#include "myMain.h"
#include "main.h"
#include <stdio.h>
#include <cstring>

#define MAGIC 				0X5A5A
#define DATA_SIZE 			18
#define PAGES_IN_BANK 		256

FLASH_EraseInitTypeDef basicFlash;
extern TEMPLIMIT tempLim;


void Flash::read()
{
	HAL_FLASH_Unlock();
	TEMPLIMIT * data = (TEMPLIMIT *)_address;
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
		_HAL_STATUS_FLASH = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,_address+(i*8),*(Data+i) );
		if(_HAL_STATUS_FLASH != HAL_OK){
			printf("HAL_FLASH_Program not OK\r\n");
			return;
		}
	}
	HAL_FLASH_Lock();
}

void Flash::erase()
{
	uint32_t pageError;  // used without interrupt

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = _page;
	basicFlash.Page = _address;
	basicFlash.NbPages = 1;

//  unlock the flash
	HAL_FLASH_Unlock();

	// erase the page from the flash (interrupt)
	_HAL_STATUS_FLASH = HAL_FLASHEx_Erase(&basicFlash, &pageError);
	if(_HAL_STATUS_FLASH != HAL_OK){
		printf("HAL_FLASHEx_Erase not OK\r\n");
		return;
	}
}



