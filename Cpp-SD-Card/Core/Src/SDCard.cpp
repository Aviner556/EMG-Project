#include "SDCard.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


//extern UART_HandleTypeDef huart2;


//void myprintf(const char *fmt, ...) {
//  static char buffer[256];
//  va_list args;
//  va_start(args, fmt);
//  vsnprintf(buffer, sizeof(buffer), fmt, args);
//  va_end(args);
//
//  int len = strlen(buffer);
//  HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, -1);
//}


void SDCARD::readSDLog()
{
	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i)\r\n", _fres);
		return;
	}

	_fres = f_open(&_fil, "temp.txt", FA_READ | FA_OPEN_EXISTING);
	if (_fres != FR_OK) {
		printf("f_open error (%i)\r\n",_fres);
		return;
	}
	//printf("'log.txt' is open for reading\r\n");


	TCHAR* rres = f_gets((TCHAR*)_readBuf, 256, &_fil);
	while(rres != 0) {
		rres = f_gets((TCHAR*)_readBuf, 256, &_fil);
		printf("%s\r\n", _readBuf);
	}
//	else {
//		printf("f_gets error (%i)\r\n", _fres);
//	}

	f_close(&_fil);

	f_mount(NULL, "", 0);

}


void SDCARD::writeSDLog()
{
	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i)\r\n", _fres);
		return;
	}

	//Now let's try and write a file "write.txt"
	_fres = f_open(&_fil, "temp.txt", FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND);
	if(_fres == FR_OK) {
		//printf("'log.txt' is open for writing\r\n");
	}
	else {
		printf("f_open error (%i)\r\n", _fres);
		return;
	}

	//Copy in a string
	strncpy((char*)_readBuf, "her will be the log info\r\n", 27);
	UINT bytesWrote;
	_fres = f_write(&_fil, _readBuf, 26, &bytesWrote);
	if(_fres == FR_OK) {
		//printf("Wrote %i bytes to 'log.txt'!\r\n", bytesWrote);
	}
	else {
		printf("f_write error (%i)\r\n",_fres);
	}

	f_close(&_fil);

	f_mount(NULL, "", 0);

}


extern "C" void mainloop()
{
	SDCARD * SDC = new SDCARD();

	HAL_Delay(1000);

	SDC->writeSDLog();
	SDC->writeSDLog();
	SDC->writeSDLog();
	SDC->readSDLog();

	while(1){}
}




