#ifndef INC_FLASH_H_
#define INC_FLASH_H_

typedef enum _FlashState
{
	STATE_IDLE,
	STATE_ERASE,
	STATE_WRITE,
}FlashState;

typedef struct _Flash
{
	FlashState flashState;
	int currentPage;
	int pageOffset;
	int writeCnt;
	int ind;
}Flash;


void Flash_init(Flash * flash);
void Flash_locPage(Flash * flash);
void Flash_erase(Flash * flash);
void Flash_write(Flash * flash);

#endif
