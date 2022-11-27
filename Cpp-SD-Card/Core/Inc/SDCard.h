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

	BYTE _readBuf[30];

public:
	SDCARD(){};
	~SDCARD(){};

	void readSDLog();
	void writeSDLog();
};





#endif /* INC_SDCARD_H_ */
