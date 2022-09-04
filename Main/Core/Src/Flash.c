#include "Flash.h"
#include <stdio.h>
#include "main.h"

static char text[256] = "hello world";

FLASH_EraseInitTypeDef basicFlash;

// address of the pages that erase and program
uint32_t * data = (uint32_t *)(0x08080000);

void Flash_init(Flash * flash)
{
	flash->flashState = STATE_IDLE;
	flash->writeCnt = 0;
	flash->ind = 0;
}

void Flash_erase(Flash * flash)
{
	//uint32_t pageError;  // used without interrupt
	//flash->flashState = STATE_ERASE;

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = 256;
	basicFlash.NbPages = 1;

	HAL_FLASH_Unlock();

	flash->flashState = STATE_WRITE;

	HAL_FLASHEx_Erase_IT(&basicFlash);
}

void Flash_write(Flash * flash)
{
	flash->writeCnt++;
	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08080000 + flash->ind, *(uint64_t *)(text + flash->ind));
	flash->ind += 8;

	if(flash->writeCnt >= 32){
		HAL_FLASH_Lock();

		flash->flashState = STATE_IDLE;
		flash->writeCnt = 0;
		flash->ind = 0;

		printf("printed from flash: %s\r\n",(char *)(data));
	}
}
