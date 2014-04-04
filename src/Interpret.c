#include "Interpret.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include "Error.h"
#include "CException.h"
#include <malloc.h>

extern Error exception;

Instruction instructionEntry[] = {	/*
									{.mnemonic = "clrwdt",.opcode = CLRWDT , .evaluate = evaluate0Parameter},
									{.mnemonic = "daw",.opcode = DAW , .evaluate = evaluate0Parameter},
									{.mnemonic = "nop",.opcode = NOP , .evaluate = evaluate0Parameter},
									{.mnemonic = "pop",.opcode = POP , .evaluate = evaluate0Parameter},
									{.mnemonic = "push",.opcode = PUSH, .evaluate = evaluate0Parameter},
									{.mnemonic = "reset",.opcode = RESET, .evaluate = evaluate0Parameter},
									{.mnemonic = "sleep",.opcode = SLEEP, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblrd*",.opcode = TBLRD, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblrd*+",.opcode = TBLRD_POSTINC, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblrd*–",.opcode = TBLRD_POSTDEC, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblrd+*",.opcode = TBLRD_PREINC, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblwt*",.opcode = TBLWT, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblwt*+",.opcode = TBLWT_POSTINC, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblwt*–",.opcode = TBLWT_POSTDEC, .evaluate = evaluate0Parameter},
									{.mnemonic = "tblwt+*",.opcode = TBLWT_PREINC, .evaluate = evaluate0Parameter},
									
									{.mnemonic = "bc", .opcode = BC, .evaluate = evaluate1Parameter},
									{.mnemonic = "bn", .opcode = BN, .evaluate = evaluate1Parameter},
									{.mnemonic = "bnc", .opcode = BNC, .evaluate = evaluate1Parameter},
									{.mnemonic = "bnn", .opcode = BNN, .evaluate = evaluate1Parameter},
									{.mnemonic = "bnov", .opcode = BNOV, .evaluate = evaluate1Parameter},
									{.mnemonic = "bnz", .opcode = BNZ, .evaluate = evaluate1Parameter},
									{.mnemonic = "bov", .opcode = BOV, .evaluate = evaluate1Parameter},
									{.mnemonic = "bra", .opcode = BRA, .evaluate = evaluate1Parameter},
									{.mnemonic = "bz", .opcode = BZ, .evaluate = evaluate1Parameter},
									{.mnemonic = "goto", .opcode = GOTO, .evaluate = evaluate1Parameter},
									{.mnemonic = "rcall", .opcode = RCALL, .evaluate = evaluate1Parameter},
									{.mnemonic = "retfie", .opcode = RETFIE, .evaluate = evaluate1Parameter},
									{.mnemonic = "retlw", .opcode = RETLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "return", .opcode = RETURN, .evaluate = evaluate1Parameter},
									{.mnemonic = "addlw", .opcode = ADDLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "andlw", .opcode = ANDLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "iorlw", .opcode = IORLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "movlb", .opcode = MOVLB, .evaluate = evaluate1Parameter},
									{.mnemonic = "movlw", .opcode = MOVLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "mullw", .opcode = MULLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "retlw", .opcode = RETLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "sublw", .opcode = SUBLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "xorlw", .opcode = XORLW, .evaluate = evaluate1Parameter},
									{.mnemonic = "call", .opcode = CALL, .evaluate = evaluate1Parameter},
									
									{.mnemonic = "movff", .opcode = MOVFF, .evaluate = evaluate2Parameter},
									{.mnemonic = "lfsr", .opcode = LFSR, .evaluate = evaluate2Parameter},
									*/
									{.mnemonic = "tstfsz", .opcode = TSTFSZ, .evaluate = evaluate1to2parameter},
									{.mnemonic = "setf", .opcode = SETF, .evaluate = evaluate1to2parameter},
									{.mnemonic = "movwf", .opcode = MOVWF, .evaluate = evaluate1to2parameter},
									{.mnemonic = "mulwf", .opcode = MULWF, .evaluate = evaluate1to2parameter},
									{.mnemonic = "negf", .opcode = NEGF, .evaluate = evaluate1to2parameter},
									{.mnemonic = "cpfseq", .opcode = CPFSEQ, .evaluate = evaluate1to2parameter},
									{.mnemonic = "cpfsgt", .opcode = CPFSGT, .evaluate = evaluate1to2parameter},
									{.mnemonic = "cpfslt", .opcode = CPFSLT, .evaluate = evaluate1to2parameter},
									{.mnemonic = "clrf", .opcode = CLRF, .evaluate = evaluate1to2parameter},
									
									{.mnemonic = "addwf", .opcode = ADDWF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "addwfc", .opcode = ADDWFC, .evaluate = evaluate1to3parameter},
									{.mnemonic = "andwf", .opcode = ANDWF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "comf", .opcode = COMF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "decf", .opcode = DECF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "decfsz", .opcode = DECFSZ, .evaluate = evaluate1to3parameter},
									{.mnemonic = "dcfsnz", .opcode = DCFSNZ, .evaluate = evaluate1to3parameter},
									{.mnemonic = "incf", .opcode = INCF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "incfsz", .opcode = INCFSZ, .evaluate = evaluate1to3parameter},
									{.mnemonic = "infsnz", .opcode = INFSNZ, .evaluate = evaluate1to3parameter},
									{.mnemonic = "iorwf", .opcode = IORWF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "movf", .opcode = MOVF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "rlcf", .opcode = RLCF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "rlncf", .opcode = RLNCF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "rrcf", .opcode = RRCF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "rrncf", .opcode = RRNCF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "subfwb", .opcode = SUBFWB, .evaluate = evaluate1to3parameter},
									{.mnemonic = "subwf", .opcode = SUBWF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "subwfb", .opcode = SUBWFB, .evaluate = evaluate1to3parameter},
									{.mnemonic = "swapf", .opcode = SWAPF, .evaluate = evaluate1to3parameter},
									{.mnemonic = "xorwf", .opcode = XORWF, .evaluate = evaluate1to3parameter},
									
									{.mnemonic = "bcf", .opcode = BCF, .evaluate = evaluate2to3parameter},
									{.mnemonic = "bsf", .opcode = BSF, .evaluate = evaluate2to3parameter},
									{.mnemonic = "btfsc", .opcode = BTFSC, .evaluate = evaluate2to3parameter},
									{.mnemonic = "btfss", .opcode = BTFSS, .evaluate = evaluate2to3parameter},
									{.mnemonic = "btg", .opcode = BTG, .evaluate = evaluate2to3parameter}};

Bytecode interpret(String *instruction) {
	String *mnemonic;
	Argument *argument;
	Bytecode bytecode;
	int i;
	
	mnemonic = getWordAndUpdate(instruction, " ");
	for(i = 0; i < 35; i++) {
		if(stringCompare(instructionEntry[i].mnemonic, mnemonic)) {
			argument = instructionEntry[i].evaluate(instruction);
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