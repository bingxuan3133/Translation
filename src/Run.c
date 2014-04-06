// Can be used after integrated with Execute.c

#include "Run.h"
#include "Interpret.h"
/*
void run(Bytecode *programCounter) {
	int i;
	
	int address = 0, nextAddress;
	
	while(programCounter != 0) {
		for(i = 0; i < 35; i++) {
			if(instructionEntry[i].opcode == programCounter[address].opcode) {
				nextAddress = programCounter[address].callBack;
				break;
			}
		}
		
		address = nextAddress;
	}
}
*/