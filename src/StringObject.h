#ifndef __STRING_OBJECT_H__
#define __STRING_OBJECT_H__

typedef struct {
	char *rawString;
	int startIndex;
	int length;
} String;

// Function Prototype
String *stringCreate(char *expression);
char *stringCopy(String *str, int relStartIndex, int length);
char *stringCopyX(String *str, int relStartIndex, int length);
int stringCompare(char *expectString, String *stringObject);
void stringLeftTrim(String* string);
void stringRightTrim(String *string);

String *getWordAndUpdate(String *line, char *delimiter);

#endif // __STRING_OBJECT_H__

 