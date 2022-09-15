#include "Flash.h"
#include <stdio.h>
#include "main.h"

#define PAGE_SIZE 2048

//static char text[256] = "hello world";

FLASH_EraseInitTypeDef basicFlash;

// address of the pages that erase and program
uint32_t* page_256_addr = (uint32_t *)(0x08080000);
uint32_t* page_257_addr = (uint32_t *)(0x08080800);

void Flash_init(Flash * flash)
{
	flash->flashState = STATE_INIT;
	flash->writeCnt = 0;
	flash->bufferSize = 8;
	flash->lenght = 8;
	flash->bufferCnt = 0;
	//define the values of "currentPage" and "pageOffset";
	Flash_locPage(flash);
	//memset(flash->flashBuffer, 0, sizeof(flash->flashBuffer));
}

void Flash_locPage(Flash * flash){
	uint64_t * page;

	// checking where the last time the flash has written. The i represent the offset from the base address.
	// if there are not free page, choose the first (page 256).
	for(int i = 0; i < PAGE_SIZE*2; i += 8){
		page = (uint64_t *)(0x08080000 + i);
		// ULL in the end = "Unsigned Long Long". keeps the value
		if(*page == 0xFFFFFFFFFFFFFFFFULL){
			if(i / PAGE_SIZE == 0){
				flash->currentPage = 256;
			}
			else{
				flash->currentPage = 257;
			}
			flash->pageOffset = i;
			return;
		}
	}
	flash->currentPage = 256;
	flash->pageOffset = 0;
}

void Flash_erase(Flash * flash)
{
	//uint32_t pageError;  // used without interrupt
	flash->flashState = STATE_ERASE;

	basicFlash.TypeErase = FLASH_TYPEERASE_PAGES;
	basicFlash.Banks = FLASH_BANK_2;
	basicFlash.Page = flash->currentPage;
	basicFlash.NbPages = 1;

//	// unlock the flash
	HAL_FLASH_Unlock();

	// erase the page from the flash (interrupt)
	HAL_FLASHEx_Erase_IT(&basicFlash);

}

void Flash_write(Flash * flash)
{
	// unlock the flash
	HAL_FLASH_Unlock();

	flash->flashState = STATE_PROGRAM;
	//flash->lenght = lenght;
	// program one byte to the flash (interrupt)
	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)page_256_addr + flash->pageOffset, *(uint64_t *)(flash->flashBuffer));
	flash->pageOffset += 8;
	flash->bufferCnt++;
	/////////////////////////////////
	/////////////////////////////////
	if(flash->bufferCnt >= 8){
//		// lock the flash
//		HAL_FLASH_Lock();
		flash->bufferCnt = 0;
//		if(flash->pageOffset <= 2048){
//			printf("printed from flash: %s. page: %d\r\n",(char *)(page_256_addr),flash->currentPage);
//		}
//		else{
//			printf("printed from flash: %s. page: %d\r\n",(char *)(page_257_addr),flash->currentPage);
		}
//	}
	/////////////////////////////////
	/////////////////////////////////
	if(flash->pageOffset == PAGE_SIZE){
		flash->currentPage = 257;
		flash->flashState = STATE_ERASE;
		printf("2048\r\n");
	}
	else if(flash->pageOffset >= PAGE_SIZE*2){
		flash->pageOffset = 0;
		flash->currentPage = 256;
		flash->flashState = STATE_ERASE;
		printf("4096\r\n");
	}
}

void Flash_Task(Flash * flash)
{
	switch(flash->flashState)
	{
		case STATE_INIT:
				break;
		case STATE_ERASE_END:
				Flash_write(flash);
				break;
		case STATE_PROGRAM_END:
//				if(flash->bufferCnt == flash->lenght){
//					flash->flashState = STATE_INIT;
//					break;
//				}
				flash->flashState = STATE_INIT;
				//Flash_write(flash);
				break;
		default:
				break;
	}
}



