#include "EvaluateParameter.h"
#include "StringObject.h"
#include <stdio.h>
#include <malloc.h>
#include "Error.h"
#include "CException.h"

Error exception;

/*
 * This function check the string is start from the specified delimiter or not
 * Input:	*string		string object that is been checking
 *			delimiter	specified delimiter that the string start from
 *
 * Return:	1	the string is start from the specified delimiter
 *			0	the string is start from other delimiter (or not delimited)
 */
int isDelimiter(String *string, char delimiter) {
	int index = string->startIndex - 1;

	while(string->rawString[index] == ' ' || string->rawString[index] == '\t') {
		index--;
	}
	if(string->rawString[index] == delimiter)
		return 1;
	else
		return 0;
}

/*
 * This function used by 1 to 2 parameter instructions to parse arguments
 */
Argument *evaluate1to2parameter(String *rawOperand) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString = malloc(sizeof(String));
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(subString->length != 0) {
		argument->operand1 = evaluate(subString);
	} else {
		Throw(INVALID_ARGUMENT);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		Throw(INVALID_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand2 = -1;
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand2 = evaluate(subString);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(isDelimiter(subString, ';') || subString->length == 0) {
		argument->operand3 = -1;
	} else {
		Throw(INVALID_ARGUMENT);
	}

finish:
	
	free(subString);
	
	return argument;
}

Argument *evaluate1to3parameter(String *rawOperand) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString = malloc(sizeof(String));
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(subString->length != 0) {
		argument->operand1 = evaluate(subString);
	} else {
	printf("1st Word");
		Throw(INVALID_ARGUMENT);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		printf("2nd Word");
		Throw(INVALID_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand2 = -1;
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand2 = evaluate(subString);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		printf("3rd Word");
		Throw(INVALID_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand3 = evaluate(subString);
	}
	
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(rawOperand);
	if(isDelimiter(subString, ';') == 0 && subString->length > 0) {
		Throw(INVALID_ARGUMENT);
	}

finish:

	return argument;
}