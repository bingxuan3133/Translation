#ifndef EvaluateParameter_H
#define EvaluateParameter_H

#include "StringObject.h"

typedef struct {
	int operand1;
	int operand2;
	int operand3;
} Argument;

typedef enum {
	ACCESS = -5,
	BANKED,
	FILEREG,
	WREG
} Operand;

typedef struct {
	char *name;
	Argument (*evaluate)(String *);
} Opcode;

int isDelimiter(String *string, char delimiter);

Argument *evaluate1to2parameter(String *parameter);

#endif // EvaluateParameter_H
