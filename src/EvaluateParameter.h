#ifndef EvaluateParameter_H
#define EvaluateParameter_H

#include "StringObject.h"

typedef struct {
	int operand1;
	int operand2;
	int operand3;
} Argument;

typedef struct {
	char *name;
	Argument (*evaluate)(String *);
} Opcode;

#endif // EvaluateParameter_H
