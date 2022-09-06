#include "Flash.h"
#include <stdio.h>
#include "main.h"

#define PAGE_SIZE 2048

static char text[256] = "hello world";

FLASH_EraseInitTypeDef basicFlash;

// address of the pages that erase and program
uint32_t* page_256_addr = (uint32_t *)(0x08080000);
uint32_t* page_257_addr = (uint32_t *)(0x08080800);

void Flash_init(Flash * flash)
{
	flash->flashState = STATE_IDLE;
	flash->writeCnt = 0;
	flash->ind = 0;
	//define the values of "currentPage" and "pageOffset";
	Flash_locPage(flash);
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

	// unlock the flash
	HAL_FLASH_Unlock();

	flash->flashState = STATE_WRITE;

	// erase the page from the flash (interrupt)
	HAL_FLASHEx_Erase_IT(&basicFlash);
}

void Flash_write(Flash * flash)
{
	//flash->writeCnt++;
	if(flash->pageOffset >= PAGE_SIZE*2){
		flash->pageOffset = 0;
		flash->currentPage = 256;
		Flash_erase(flash);
		printf("4096");
	}
	// program one byte to the flash (interrupt)
	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)page_256_addr + flash->pageOffset, *(uint64_t *)(text + flash->ind));
	flash->pageOffset += 8;
	flash->ind += 8;
	/////////////////////////////////
	/////////////////////////////////
	if(flash->ind >= 256){
		flash->ind = 0;
		printf("printed from flash: %s\r\n",(char *)(page_256_addr));
	}
	/////////////////////////////////
	/////////////////////////////////
	if(flash->pageOffset == PAGE_SIZE){
		flash->currentPage = 257;
		Flash_erase(flash);
		printf("2048");
	}

//	// when finished to write 32 bytes
//	if(flash->writeCnt >= 32){
//		// lock flash
//		HAL_FLASH_Lock();
//
//		flash->flashState = STATE_IDLE;
//		flash->writeCnt = 0;
//		flash->ind = 0;
//
//		printf("printed from flash: %s\r\n",(char *)(page_256_addr));
//	}
}
