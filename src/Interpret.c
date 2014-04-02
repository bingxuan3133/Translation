#include "Interpret.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include <malloc.h>

Instruction instructionEntry[] = {{.mnemonic = "movwf", .opcode = MOVWF, .evaluate = evaluate1to2parameter}};

Bytecode interpret(String *instruction) {
	String *mnemonic;
	Argument *argument;
	Bytecode bytecode;
	
	mnemonic = getWordAndUpdate(instruction, " ");
	if(stringCompare(instructionEntry[0].mnemonic, mnemonic))
		argument = instructionEntry[0].evaluate(instruction);
		
	bytecode.opcode = instructionEntry[0].opcode;
	bytecode.operand1 = argument->operand1;
	bytecode.operand2 = argument->operand2;
	bytecode.operand3 = argument->operand3;
	
	free(mnemonic);
	free(argument);
	
	return bytecode;
}