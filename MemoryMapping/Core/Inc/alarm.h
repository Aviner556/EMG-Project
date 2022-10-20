#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#include <stdio.h>

typedef struct _MemoryMaping
{
	uint16_t magicNumber; //(two bytes) – 0x5A5A
	uint32_t version; //(four bytes) – Major.Minor.Release.Build
	uint8_t applicationType; //(one byte) – 1 for alarms project
	uint32_t crc; //(four bytes) – for future use
	uint8_t flags; //(four bytes) – for future use
}MemoryMaping;


void MemoryMap_print(const MemoryMaping * memMap);


#endif /* INC_ALARM_H_ */
