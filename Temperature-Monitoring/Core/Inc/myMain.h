#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_

#include <stdint.h>


struct TEMPLIMIT
{
	double warning = 50;
	double critical = 60;
	uint16_t magicNum = 0X5A5A;
};


enum ALERT
{
	NORMAL_STATE,
	WARNING_STATE,
	CRITICAL_STATE,
};


typedef struct _LOG
{
	char severity[9];
	char message[40];
}LOG;

void createLog(char * bufferLog, LOG log);



#endif /* INC_MYMAIN_H_ */
