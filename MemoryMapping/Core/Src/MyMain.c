#include "alarm.h"
#include "main.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

//define the struct
const MemoryMaping memMap = {.magicNumber = 0x5A5A,
							 .version = (1<<0) | (1<<8) | (3<<16) | (5<<24),
							 .applicationType = 1,
							 .crc = 0,
							 .flags = 0,
};

void mainloop()
{
	MemoryMap_print(&memMap);

	while(1){

	}
}





