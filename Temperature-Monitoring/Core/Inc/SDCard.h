#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include "fatfs.h"


class SDCARD
{
private:
	//some variables for FatFs
	FATFS _FatFs; 	//Fatfs handle
	FIL _fil; 		//File handle
	FRESULT _fres; //Result after operations

	BYTE _readBuf[256];

public:
	SDCARD(){};
	~SDCARD(){};

	void readSDLog();
	void writeSDLog(char * bufferLog);
};

//void myprintf(const char *fmt, ...);


#endif /* INC_SDCARD_H_ */
