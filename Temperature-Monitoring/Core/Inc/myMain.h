#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_

typedef struct _TEMPLIMIT
{
	double warning = 50;
	double critical = 60;
	uint16_t magicNum = 0X5A5A;
}TEMPLIMIT;

typedef enum _ALERT
{
	NORMAL_STATE,
	WARNING_STATE,
	CRITICAL_STATE,
}ALERT;





#endif /* INC_MYMAIN_H_ */
