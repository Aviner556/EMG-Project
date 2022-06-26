#ifndef _BINARY_PROTOCOL_H_
#define _BINARY_PROTOCOL_H_

enum State
{
	WIATING_FOR_SOM,
	WIATING_FOR_LEN,
	WIATING_FOR_MSGID,
	WIATING_FOR_SEQID,
	WIATING_FOR_CHECKSUM,
	READ_PAYLOAD,
	ERROR,
	STOP
};

typedef struct _MessageHeader
{
	uint8_t length;
	uint8_t messageId;
	uint8_t sequenceId;
	uint8_t checksum;
}MessageHeader;

typedef struct _Message
{
	struct _MessageHeader header;
	uint8_t payload[100];
}Message;


int checkState(uint8_t *ch);

#endif
