#include "Flash.h"
#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"

#define PAGE_SIZE 2048

FLASH_EraseInitTypeDef basicFlash;

// address of the pages that erase and program
uint32_t* page_256_addr = (uint32_t *)(0x08080000);

void Flash_init(Flash * flash)
{
	flash->flashState = STATE_INIT;
	flash->pageOffset = 0;
	flash->writeCnt = 0;
}

void Flash_erase(Flash * flash)
{
	//uint32_t pageError;  // used without interrupt
	flash->flashState = STATE_ERASE;

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = 256;
	basicFlash.NbPages = 1;

	// unlock the flash
	HAL_FLASH_Unlock();

	// erase the page from the flash (interrupt)
	uint32_t pageError = 0;
	HAL_FLASHEx_Erase(&basicFlash, &pageError);
}

void Flash_write(Flash * flash, void * data, uint32_t sizeOfData)
{
	// unlock the flash
	HAL_FLASH_Unlock();

	flash->flashState = STATE_PROGRAM;
	// program one byte to the flash (interrupt)
	for(int i = 0; i < sizeOfData/8; i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)page_256_addr + flash->pageOffset, *(uint64_t *)(data+ flash->pageOffset));
		flash->pageOffset += 8;
	}
	flash->pageOffset = 0;
}



/* USER CODE END Header_entry_FlashTask */
void entry_FlashTask(void *argument)
{
  /* USER CODE BEGIN entry_FlashTask */
  /* Infinite loop */
  while(1)
  {
    osDelay(1);
  }
  /* USER CODE END entry_FlashTask */
}

