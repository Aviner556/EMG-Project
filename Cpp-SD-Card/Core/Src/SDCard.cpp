#include "SDCard.h"
#include <stdio.h>
#include <string.h>



void SDCARD::readSDLog()
{
	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i)\r\n", _fres);
		return;
	}
	//Open the file system
	_fres = f_mount(&_FatFs, "", 1); //1=mount now
	if(_fres != FR_OK) {
		printf("f_mount error (%i)\r\n", _fres);
		return;
	}

	_fres = f_open(&_fil, "log.txt", FA_READ);
	if (_fres != FR_OK) {
		printf("f_open error (%i)\r\n",_fres);
		return;
	}
	printf("'log.txt' is open for reading\r\n");


	TCHAR* rres = f_gets((TCHAR*)_readBuf, 30, &_fil);
	if(rres != 0) {
		printf("Read string from 'log.txt' contents: %s\r\n", _readBuf);
	}
	else {
		printf("f_gets error (%i)\r\n", _fres);
	}

	f_close(&_fil);

	f_mount(NULL, "", 0);
}


void SDCARD::writeSDLog()
{
	//Now let's try and write a file "write.txt"
	_fres = f_open(&_fil, "log.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if(_fres == FR_OK) {
		printf("'log.txt' is open for writing\r\n");
	}
	else {
		printf("f_open error (%i)\r\n", _fres);
		return;
	}

	//Copy in a string
	strncpy((char*)_readBuf, "her will be the log info", 25);
	UINT bytesWrote;
	_fres = f_write(&_fil, _readBuf, 24, &bytesWrote);
	if(_fres == FR_OK) {
		printf("Wrote %i bytes to 'log.txt'!\r\n", bytesWrote);
	}
	else {
		printf("f_write error (%i)\r\n",_fres);
	}

	f_close(&_fil);

	f_mount(NULL, "", 0);
}
