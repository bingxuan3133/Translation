#include "EvaluateParameter.h"
#include "StringObject.h"
#include "Error.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>

extern Error exception;

/*
 * This function check if the string is previously delimited by the specified delimiter or not
 *
 * Input:	
 *		*string		String object that is been checking
 *		delimiter	Specified delimiter that previously delimit the string
 *
 * Return:	
 *		1	The string is previously delimited by the specified delimiter
 *		0	The string previously delimited by other delimiter (or not delimited)
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
 * This function used by 1 to 2 Parameter instructions to parse arguments
 *
 * Input:	
 *		*rawOperand		Whole line of Parameter after the opcode get extracted
 *
 * Return:
 *		argument		Argument type object that stores operands
 */
Argument *evaluate1to2Parameter(String *rawOperand) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString = malloc(sizeof(String));
	
	// 1st Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(subString->length != 0) {
		argument->operand1 = evaluate(subString);
	} else {
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}
	
	// 2nd Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		Throw(NO_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand2 = -1;
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand2 = evaluate(subString);
	}
	
	// check for invalid Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if((isDelimiter(subString, ';') || subString->length == 0) && isDelimiter(subString, ',') == 0){ // is a comment or a zero length string and it is not a Parameter
		argument->operand3 = -1;
	} else {
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}

finish:
	
	free(subString);
	
	return argument;
}

/*
 * This function used by 1 to 3 Parameter instructions to parse arguments
 *
 * Input:	
 *		*rawOperand		Whole line of Parameter after the opcode get extracted
 *
 * Return:
 *		argument		Argument type object that stores operands
 */
Argument *evaluate1to3Parameter(String *rawOperand) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString = malloc(sizeof(String));
	
	// 1st Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(subString->length != 0) {
		argument->operand1 = evaluate(subString);
	} else {
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}
	
	// 2nd Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		Throw(NO_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand2 = -1;
		argument->operand3 = -1;
		goto finish;
	} else { // subString->length != 0
		if(subString->length == 1 && subString->rawString[subString->startIndex] == 'f') {
			argument->operand2 = 1;
		} else if(subString->length == 1 && subString->rawString[subString->startIndex] == 'w') {
			argument->operand2 = 0;
		} else {
			argument->operand2 = evaluate(subString);
		}
	}

	// 3rd Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		Throw(NO_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand3 = evaluate(subString);
	}
	
	// check for invalid Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if((isDelimiter(subString, ';') == 0 && subString->length > 0) || isDelimiter(subString, ',')) { // is not a comment and a string of the length is more than zero
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}

finish:

	free(subString);

	return argument;
}

/*
 * This function used by 2 to 3 Parameter instructions to parse arguments
 *
 * Input:	
 *		*rawOperand		Whole line of Parameter after the opcode get extracted
 *
 * Return:
 *		argument		Argument type object that stores operands
 */
Argument *evaluate2to3Parameter(String *rawOperand) {
	Argument *argument = malloc(sizeof(Argument));
	String *subString = malloc(sizeof(String));
	
	// 1st Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(subString->length != 0) {
		argument->operand1 = evaluate(subString);
	} else {
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}
	
	// 2nd Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(subString->length != 0) {
		argument->operand2 = evaluate(subString);
	} else {
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}
	
	// 3rd Parameter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if(isDelimiter(subString, ',') == 1 && subString->length == 0) {
		Throw(NO_ARGUMENT);
	} else if(isDelimiter(subString, ';') == 1 || subString->length == 0) {
		argument->operand3 = -1;
		goto finish;
	} else {
		argument->operand3 = evaluate(subString);
	}
	
	// check for invalid paramter
	stringLeftTrim(rawOperand);
	subString = getWordAndUpdate(rawOperand, ",;");
	stringRightTrim(subString);
	if((isDelimiter(subString, ';') == 0 && subString->length > 0) || isDelimiter(subString, ',')) {
		Throw(INVALID_LENGTH_OF_ARGUMENT);
	}

finish:

	free(subString);

	return argument;
}
