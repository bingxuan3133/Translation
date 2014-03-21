#include "EvaluateParameter.h"
#include "StringObject.h"
#include <stdio.h>
#include <malloc.h>

Argument *evaluate1to2parameter(String *parameter) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString;
	char* buffer;
	
	subString = getWordAndUpdate(parameter, ",;");
	if(subString->length != 0) {
		buffer = stringCopy(subString, 0, subString->length);
		argument->operand1 = shuntingYard(buffer);
	} else {
		argument->operand1 = -1;
	}
	
	stringLeftTrim(parameter);
	subString = getWordAndUpdate(parameter, ",;");
	if(subString->length != 0) {
		buffer = stringCopy(subString, 0, subString->length);
		argument->operand2 = shuntingYard(buffer);
	} else {
		argument->operand2 = -1;
	}
	
	argument->operand3 = -1;
	
	return argument;
}