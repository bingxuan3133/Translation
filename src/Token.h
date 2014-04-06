#ifndef Token_H
#define Token_H

#include "StringObject.h"

typedef enum {NUMBER,OPERATOR,IDENTIFIER}Token;

int evaluate(String *expression);

#endif // Token_H