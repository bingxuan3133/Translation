#ifndef Interpret_H
#define Interpret_H

#include "EvaluateParameter.h"

typedef enum {	TSTFSZ,
				SETF,
				MOVWF,
				MULWF,
				NEGF,
				CPFSEQ,
				CPFSGT,
				CPFSLT,
				CLRF,
				ADDWF,
				ADDWFC,
				ANDWF,
				COMF,
				DECF,
				DECFSZ,
				DCFSNZ,
				INCF,
				INCFSZ,
				INFSNZ,
				IORWF,
				MOVF,
				RLCF,
				RLNCF,
				RRCF,
				RRNCF,
				SUBFWB,
				SUBWF,
				SUBWFB,
				SWAPF,
				XORWF,
				BCF,
				BSF,
				BTFSC,
				BTFSS,
				BTG} Opcode;

typedef struct {
	Opcode opcode;
	int operand1;
	int operand2;
	int operand3;
	int absoluteAddress;
} Bytecode;

typedef struct {
	char *mnemonic;
	Opcode opcode;
	Argument *(*evaluateParameter)(String *);
	int (*execute)(Bytecode);
} Instruction;

Bytecode interpret(String *instruction);

#endif // Interpret_H
