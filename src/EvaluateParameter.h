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

int isDelimiter(String *string, char delimiter);

Argument *evaluate0Parameter(String *rawOperand);
Argument *evaluate1Parameter(String *rawOperand);
Argument *evaluate2Parameter(String *rawOperand);
Argument *evaluate1to2Parameter(String *rawOperand);
Argument *evaluate1to3Parameter(String *rawOperand);
Argument *evaluate2to3Parameter(String *rawOperand);

#endif // EvaluateParameter_H
