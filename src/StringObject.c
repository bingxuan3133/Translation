#include "StringObject.h"
#include "Token.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
 * This function is to generate a string object
 *
 * Input: *expression 		which contain the string(expression)
 * Output: none
 * return: newString 		A string object which contains the info of a string
 */
String *stringCreate(char *expression) {
	int length = strlen(expression);
	String *newString = malloc (sizeof(String));
	String *string;
	string	= newString;
	int result;
	char *newRawString = malloc (length+1);
	int tempIndex,stringStartLocation,j=0; 
	Token *newToken;

	stringCopy(expression, newRawString, 0, length);
	newString->rawString = newRawString;
	newString->startIndex = 0;
	newString->length = strlen(newString->rawString);
	/*
	for(tempIndex=0;tempIndex<=string->length;tempIndex++)
	{
		// result = convertBasedNumberToBase10Number(newString->rawString);
		
		if (isalpha(string->rawString[tempIndex])||(string->rawString[tempIndex])=='.')
		{
			char *name = malloc (string->length);
			stringStartLocation=tempIndex;
			do
			{
				j++;
				tempIndex++;
			}while(isalnum(string->rawString[tempIndex])||(string->rawString[tempIndex]=='.'));
			stringCopy(string->rawString,name,stringStartLocation,j);
			newToken=checkIdentifier(name);
			
			if(newToken==NULL)
			{
				string = getFromListAndUpdate(newString, name);
				newString = string;
			}
		}
	}
	
	*/
	return newString;
}

/*
	This function is to copy string from the middle of the string for specific length.
	
	input :
	*source				The string that contain the wanted string.
	startLocation		The start location of the wanted string in source
	length 				The length of the wanted string 
	
	output:
	*destination 		The wanted string will be copied to this string.(must be in array to make this work)
	
	return:
	none
*/
void stringCopy(char *source, char*destination, int startLocation, int length) {
	int i, j = 0;

	for (i = 0; i < length; i++, j++) {
		destination[j]= source[startLocation+i];
	}

	destination[j] = '\0';
}

/*
 * This function is to copy string from the middle of the string for specific length.
 * 
 * Input :
 * *source				The string object which contains the wanted string
 * relStartIndex		The relative start location of the wanted string source
 * length 				The length of the wanted string 
 * 
 * Output:
 * *destination 		The wanted string will be copied to this string.(must be in array to make this work)
 *	
 * return:
 * none
 */
char *stringCopyX(String *source, int relStartIndex, int length) {
	char *destination = malloc(sizeof(char)*(length+1));
	int j = relStartIndex + source->startIndex;
	int i;
	
	for(i = 0; i < length; i++, j++)
		destination[i] = source->rawString[j];

	destination[i] = 0;
	
	return destination;
}

/*
 * This function is to compare a string object with a character string (Due to strcmp cannot compare symbol)
 * 
 * Input :
 *	*expectedString	The string object which contains the wanted string
 * 	*stringObject	The relative start location of the wanted string source
 *
 * Return:
 * 	1				stringObject same with the expectedString
 * 	0				stringObject is not same with the expectedString
 */
int stringCompare(char *expectedString, String *stringObject) {
	int i = 0, j = stringObject->startIndex;

		for(i = 0; expectedString[i] != 0; i++) {
			if(expectedString[i] != stringObject->rawString[j]) {
				return 0;
			}
			j++;
		}
		
		if(i == stringObject->length) {
			return 1;
		} else {
			return 0;
		}
}

/*
 * This function is to compare a string object with a character string ignoring case sensitivity
 * 
 * Input :
 *	*expectedString	The string object which contains the wanted string
 * 	*stringObject	The relative start location of the wanted string source
 *
 * Return:
 * 	1				stringObject same with the expectedString ignoring case sensitivity
 * 	0				stringObject is not same with the expectedString ignoring case sensitivity
 */
int stringCompareIgnoreCase(char *expectedString, String *stringObject) {
	int i = 0, j = stringObject->startIndex;

		for(i = 0; expectedString[i] != 0; i++) {
			if(isalpha(expectedString[i])) { // for alphabet
				if(islower(expectedString[i])) {
					if((expectedString[i] != stringObject->rawString[j]) && (toupper(expectedString[i]) != stringObject->rawString[j]))
						return 0;
				} else { // isupper(expectedString[i])
					if((expectedString[i] != stringObject->rawString[j]) && (tolower(expectedString[i]) != stringObject->rawString[j]))
						return 0;
				}
			} else { // for symbol
				if(expectedString[i] != stringObject->rawString[j]) {
					return 0;
				}
			}
			j++;
		}
		
		if(i == stringObject->length) {
			return 1;
		} else {
			return 0;
		}
}

/*
 * This function is to trim out the left space/tab of string
 *
 * Input:
 *	string		word or line of string
 */
void stringLeftTrim(String *string) {
	while(string->rawString[string->startIndex] == ' ' || string->rawString[string->startIndex] == '\t' ) {
		string->startIndex++;
		string->length--;
	}
}

/*
 * This function is to trim out the right space/tab of string
 *
 * Input:
 *	string		word or line of string
 */
void stringRightTrim(String *string) {
	int i = string->startIndex;
	while((string->rawString[i + string->length - 1] == ' ' || string->rawString[i + string->length - 1] == '\t') && string->length != 0) {
		string->length--;
	}
}

/*
 * This function is to get word from a line according to delimiters and update the status of the line (startIndex and length)
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
				goto delimited;
			}
		}
		line->startIndex++;
		word->length++;
		i++;
	}
	
delimited:
	
	line->length = line->length - i;
	
	return word;
}

