#include "Interpret.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include "Error.h"
#include "CException.h"
#include <malloc.h>

extern Error exception;

Instruction instructionEntry[] = {	/*
									{.mnemonic = "clrwdt",.opcode = CLRWDT , .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "daw",.opcode = DAW , .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "nop",.opcode = NOP , .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "pop",.opcode = POP , .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "push",.opcode = PUSH, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "reset",.opcode = RESET, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "sleep",.opcode = SLEEP, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblrd*",.opcode = TBLRD, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblrd*+",.opcode = TBLRD_POSTINC, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblrd*–",.opcode = TBLRD_POSTDEC, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblrd+*",.opcode = TBLRD_PREINC, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblwt*",.opcode = TBLWT, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblwt*+",.opcode = TBLWT_POSTINC, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblwt*–",.opcode = TBLWT_POSTDEC, .evaluateParameter = evaluate0Parameter},
									{.mnemonic = "tblwt+*",.opcode = TBLWT_PREINC, .evaluateParameter = evaluate0Parameter},
									
									{.mnemonic = "bc", .opcode = BC, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bn", .opcode = BN, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bnc", .opcode = BNC, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bnn", .opcode = BNN, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bnov", .opcode = BNOV, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bnz", .opcode = BNZ, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bov", .opcode = BOV, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bra", .opcode = BRA, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "bz", .opcode = BZ, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "goto", .opcode = GOTO, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "rcall", .opcode = RCALL, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "retfie", .opcode = RETFIE, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "retlw", .opcode = RETLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "return", .opcode = RETURN, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "addlw", .opcode = ADDLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "andlw", .opcode = ANDLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "iorlw", .opcode = IORLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "movlb", .opcode = MOVLB, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "movlw", .opcode = MOVLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "mullw", .opcode = MULLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "retlw", .opcode = RETLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "sublw", .opcode = SUBLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "xorlw", .opcode = XORLW, .evaluateParameter = evaluate1Parameter},
									{.mnemonic = "call", .opcode = CALL, .evaluateParameter = evaluate1Parameter},
									
									{.mnemonic = "movff", .opcode = MOVFF, .evaluateParameter = evaluate2Parameter},
									{.mnemonic = "lfsr", .opcode = LFSR, .evaluateParameter = evaluate2Parameter},
									*/
									{.mnemonic = "tstfsz", .opcode = TSTFSZ, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "setf", .opcode = SETF, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "movwf", .opcode = MOVWF, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "mulwf", .opcode = MULWF, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "negf", .opcode = NEGF, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "cpfseq", .opcode = CPFSEQ, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "cpfsgt", .opcode = CPFSGT, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "cpfslt", .opcode = CPFSLT, .evaluateParameter = evaluate1to2Parameter},
									{.mnemonic = "clrf", .opcode = CLRF, .evaluateParameter = evaluate1to2Parameter},
									
									{.mnemonic = "addwf", .opcode = ADDWF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "addwfc", .opcode = ADDWFC, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "andwf", .opcode = ANDWF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "comf", .opcode = COMF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "decf", .opcode = DECF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "decfsz", .opcode = DECFSZ, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "dcfsnz", .opcode = DCFSNZ, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "incf", .opcode = INCF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "incfsz", .opcode = INCFSZ, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "infsnz", .opcode = INFSNZ, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "iorwf", .opcode = IORWF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "movf", .opcode = MOVF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "rlcf", .opcode = RLCF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "rlncf", .opcode = RLNCF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "rrcf", .opcode = RRCF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "rrncf", .opcode = RRNCF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "subfwb", .opcode = SUBFWB, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "subwf", .opcode = SUBWF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "subwfb", .opcode = SUBWFB, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "swapf", .opcode = SWAPF, .evaluateParameter = evaluate1to3Parameter},
									{.mnemonic = "xorwf", .opcode = XORWF, .evaluateParameter = evaluate1to3Parameter},
									
									{.mnemonic = "bcf", .opcode = BCF, .evaluateParameter = evaluate2to3Parameter},
									{.mnemonic = "bsf", .opcode = BSF, .evaluateParameter = evaluate2to3Parameter},
									{.mnemonic = "btfsc", .opcode = BTFSC, .evaluateParameter = evaluate2to3Parameter},
									{.mnemonic = "btfss", .opcode = BTFSS, .evaluateParameter = evaluate2to3Parameter},
									{.mnemonic = "btg", .opcode = BTG, .evaluateParameter = evaluate2to3Parameter}};

/**
 * This function interpret an instruction to known byte code
 *
 * Input:
 * 	instruction		A line of instruction which is String struct
 * Return:
 *	bytecode		Known byte code
 */
Bytecode interpret(String *instruction) {
	String *mnemonic;
	Argument *argument;
	Bytecode bytecode;
	int i;
	
	mnemonic = getWordAndUpdate(instruction, " ");
	for(i = 0; i < 35; i++) {
		if(stringCompareIgnoreCase(instructionEntry[i].mnemonic, mnemonic)) {
			argument = instructionEntry[i].evaluateParameter(instruction);
			bytecode.opcode = instructionEntry[i].opcode;
			goto foundOpcode;
		}
	}
	
	Throw(INVALID_OPCODE);
	
foundOpcode:
	
	bytecode.operand1 = argument->operand1;
	bytecode.operand2 = argument->operand2;
	bytecode.operand3 = argument->operand3;
	
	free(mnemonic);
	free(argument);
	
	return bytecode;
}

/**
 * This function interpret all instruction from a .txt file
 *
 * Input:
 * 	programCode		An array of Bytecode to store bytecodes
 */
void interpretAll(Bytecode *programCode) {
	int address = 0;
	String* string;
	
	while((string = readLine()) != NULL) {
		programCode[address] = interpret(string);
		programCode[address].absoluteAddress = address;
		address++;

		free(string);
	} ;
}
