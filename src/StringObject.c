#include "StringObject.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
 * This function will generate a string
 *
 * Input: *expression 		which contain the string(expression)
 * Output: none
 * return: Tokenizer 		which pass to the getToken to generate token.
 */
String *stringCreate(char *expression) {
	int length = strlen(expression);
	String *newString = malloc (sizeof(String));
	char *newRawString = malloc (length+1);
	
	newRawString = expression;
	newString->rawString = newRawString;
	newString->startIndex = 0;
	newString->length = strlen(newString->rawString);
	
	return newString;
}

/*
 * This function is to copy string from the middle of the string for specific length.
 * 
 * input :
 * *source				The string that contain the wanted string.
 * startLocation		The start location of the wanted string in source
 * length 				The length of the wanted string 
 * 
 * output:
 * *destination 		The wanted string will be copied to this string.(must be in array to make this work)
 *	
 * return:
 * none
 */
char *stringCopy(String *source, int relStartIndex, int length) {
	char *destination = malloc(sizeof(char)*(length+1));
	int j = relStartIndex + source->startIndex;
	int i;
	
	for(i = 0; i < length; i++, j++)
		destination[i] = source->rawString[j];

	destination[i] = 0;
	
	return destination;
}

/*
 * Trim out the left space/tab of string
 *
 * Input:
 *	string	word or line of string
 */
void stringLeftTrim(String *string) {
	while(string->rawString[string->startIndex] == ' ' || string->rawString[string->startIndex] == '\t' ) {
		string->startIndex++;
		string->length--;
	}
}

/*
 * Trim out the right space/tab of string
 *
 * Input:
 *	string	word or line of string
 */
void stringRightTrim(String *string) {
	while(string->rawString[string->length - 1] == ' ' || string->rawString[string->length - 1] == '\t') {
		string->length--;
	}
}

/*
 * Get word from a line according to delimiters and update the status of the line (startIndex and length)
 *
 * Input:
 *	line		A line of string
 *	delimiter	Symbol to separate words
 *
 * Return:
 *	word		First word from a line
 */
String *getWordAndUpdate(String *line, char *delimiter) {
	String *word = malloc(sizeof(String));
	int i; // Act as loop counter to avoid access beyond end of string
	int j;

	word->rawString = line->rawString;
	word->startIndex = line->startIndex;
	word->length = 0;
	
	i = 0;
	while(i < line->length) {
		for(j = 0; delimiter[j] != 0; j++) {
			if(line->rawString[line->startIndex] == delimiter[j]) {
				line->startIndex++;
				i++;
				goto finish;
			}
		}
		line->startIndex++;
		word->length++;
		i++;
	}
	
finish:
	
	line->length = line->length - i;
	
	return word;
}

