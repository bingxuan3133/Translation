#include "EvaluateParameter.h"
#include "StringObject.h"
#include <stdio.h>
#include <malloc.h>

// global variable cannot malloc and it cannot be an array
// if it is a pointer, it was initialized as pointing to NULL and then malloc
// ExpectAndReturn will be called before the real function is called
// ExpectAndReturn takes NULL as expectation, BUT in real function -> shuntingYard takes 0x10 (as it is malloced)

Argument *evaluate1to2parameter(String *parameter) {
	Argument *argument;
	subString = getWordAndUpdate(parameter, ";");
	
	stringCopy(subString->rawString, &tempCharArray[0], subString->startIndex, subString->length);// <- destination must be array 
	argument->operand1 = shuntingYard(&tempCharArray[0]);
	
	return argument;
}