#include "alarm.h"

extern MemoryMaping memMap;

void MemoryMap_print(const MemoryMaping * memMap)
{
	/*
	 * "version" is uint64_t, and by inserting it into uint8_t we received only the first byte.
	 * by pushing the bits to the right with ">>" we can insert different byte each time.
	 */
	uint8_t Major = memMap->version;
	uint8_t Minor = memMap->version >> 8;
	uint8_t Release = memMap->version >> 16;
	uint8_t Build = memMap->version >> 24;

	printf("ver: %d.%d.%d.%d\r\n",Major, Minor, Release, Build);
}
