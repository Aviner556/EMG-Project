#include "binaryProtocol.h"
static State currentState = WIATING_FOR_SOM;
_MessageHeader HM;

int checkState(uint8_t ch)
{
	switch(currentState)
	{
	case WIATING_FOR_SOM:
		if(ch == 0XAA){
			currentState = WIATING_FOR_LEN;
		}
		break;
	case WIATING_FOR_LEN:
		HM.lenght = ch;
		currentState = WIATING_FOR_MSGID;
		break;
	case WIATING_FOR_MSGID:
		HM.messageId = ch;
		currentState = WIATING_FOR_CHECKSUM;
		break;
	case WIATING_FOR_CHECKSUM:
		//continue
		if(ch == 0){
			currentState = READ_PAYLOAD;
		}
		break;
	case READ_PAYLOAD:

	}
}
