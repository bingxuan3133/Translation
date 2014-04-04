#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum {INVALID_LENGTH_OF_ARGUMENT, NO_ARGUMENT, INVALID_OPCODE} Error;

typedef struct{
	char *rawString;
	int position;
	char *message;
} ErrorMessage;

extern ErrorMessage errorMessage;

#endif //__ERROR_H__