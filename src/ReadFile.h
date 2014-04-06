#ifndef ReadFile_H
#define ReadFile_H

#include "StringObject.h"

String *readLine(); // return StringObject type to make mocking pass
					// if stringCreate function is used instead, another memory is allocation
					// hence memory mismatch

#endif // ReadFile_H