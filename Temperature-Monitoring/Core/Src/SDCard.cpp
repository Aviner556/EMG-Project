#include "SDCard.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fstream>


void SDCARD::readSDLog(char * fileName)
{
	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i) on readSDLog\r\n", _fres);
		return;
	}

	_fres = f_open(&_fil, fileName, FA_READ | FA_OPEN_EXISTING);
	if (_fres != FR_OK) {
		printf("f_open error (%i) on readSDLog\r\n",_fres);
		return;
	}

	TCHAR* rres = f_gets((TCHAR*)_readBuf, 256, &_fil);
	if(rres == 0){
		printf("f_gets error (%i)\r\n", _fres);
		printf("file is empty or missing\r\n");
	}
	while(rres != 0) {
		rres = f_gets((TCHAR*)_readBuf, 256, &_fil);
		printf("%s\r\n", _readBuf);
	}

	f_close(&_fil);

	f_mount(NULL, "", 0);
}


void SDCARD::writeSDLog(char * fileName)
{
	UINT bytesWrote;

	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i) on writeSDLog\r\n", _fres);
		return;
	}

	//Now let's try and write a file "write.txt"
	_fres = f_open(&_fil, fileName, FA_WRITE | FA_OPEN_EXISTING | FA_OPEN_APPEND);
	if(_fres != FR_OK) {
		printf("f_open error (%i) on writeSDLog\r\n", _fres);
		_fres = f_open(&_fil, fileName, FA_CREATE_ALWAYS);
		if(_fres == FR_OK) {
			printf("%s was created!\r\n",fileName);
		}
		return;
	}

	_fres = f_write(&_fil, _bufferLog, strlen(_bufferLog), &bytesWrote);
	if(_fres != FR_OK) {
		printf("f_write error (%i)\r\n",_fres);
	}

	f_close(&_fil);

	f_mount(NULL, "", 0);
}


void SDCARD::clearSDLog()
{
	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i) on clearSDLog\r\n", _fres);
		return;
	}
	//Now let's try and write a file "write.txt"
	_fres = f_open(&_fil, "log.txt", FA_CREATE_ALWAYS);
	if(_fres != FR_OK) {
		printf("f_open error (%i) on writeSDLog\r\n", _fres);
		return;
	}

	f_close(&_fil);

	f_mount(NULL, "", 0);
}

