#include "EvaluateParameter.h"
#include "StringObject.h"
#include <stdio.h>
#include <malloc.h>
#include "Error.h"
#include "CException.h"

Error exception;

int isComment(String *rawOperand) {
	int index = rawOperand->startIndex - 1;

	while(rawOperand->rawString[index] == ' ' || rawOperand->rawString[index] == '\t') {
		index--;
	}
	if(rawOperand->rawString[index] == ';')
		return 1;
	else
		return 0;
}

Argument *evaluate1to2parameter(String *rawOperand) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString = malloc(sizeof(String));
	
	subString = getWordAndUpdate(rawOperand, ",;");
	if(subString->length != 0) {
		argument->operand1 = evaluate(subString);
	} else {
		Throw(INVALID_ARGUMENT);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	if(isComment(subString) == 1 || subString->length == 0) {
		argument->operand2 = -1;
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand2 = evaluate(subString);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	if(subString->length == 0) {
		argument->operand3 = -1;
	} else {
		Throw(INVALID_ARGUMENT);
	}

	finish:
	
	free(subString);
	
	return argument;
}