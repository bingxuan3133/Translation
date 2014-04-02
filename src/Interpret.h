#ifndef Interpret_H
#define Interpret_H

#include "EvaluateParameter.h"

typedef enum {MOVWF} Opcode;

typedef struct {
	Opcode opcode;
	int operand1;
	int operand2;
	int operand3;
} Bytecode;

typedef struct {
	char *mnemonic;
	Opcode opcode;
	Argument *(*evaluate)(String *); 
} Instruction;

Bytecode interpret(String *instruction);

#endif // Interpret_H
