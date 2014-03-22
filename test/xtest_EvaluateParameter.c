#include "unity.h"
#include "EvaluateParameter.h"
#include "mock_StringObject.h"
#include "mock_Token.h"
#include <malloc.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_evaluate1to2parameter_should_pass_one_parameter_from_rawString_to_argument () {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10" , .startIndex = 6, .length = 4};
	String argument1 = {.rawString = "movwf 0x10" , .startIndex = 6, .length = 4};
	String argument2 = {.rawString = "movwf 0x10" , .startIndex = 10, .length = 0};
	
	getWordAndUpdate_ExpectAndReturn(&parameter, ",;", &argument1);
	evaluate_ExpectAndReturn(&argument1, 0x10);
	
	stringLeftTrim_Expect(&parameter);
	getWordAndUpdate_ExpectAndReturn(&parameter, ";", &argument2);
	
	argument = evaluate1to2parameter(&parameter);
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(-1, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to2parameter_should_pass_two_parameter_from_rawString_to_argument () {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10, ACCESS" , .startIndex = 6, .length = 12};
	String argument1 = {.rawString = "movwf 0x10, ACCESS" , .startIndex = 6, .length = 4};
	String argument2 = {.rawString = "movwf 0x10, ACCESS" , .startIndex = 12, .length = 6};
	
	getWordAndUpdate_ExpectAndReturn(&parameter, ",;", &argument1);
	evaluate_ExpectAndReturn(&argument1, 0x10);
	
	stringLeftTrim_Expect(&parameter);
	getWordAndUpdate_ExpectAndReturn(&parameter, ";", &argument2);
	evaluate_ExpectAndReturn(&argument2, -5);
	
	argument = evaluate1to2parameter(&parameter);
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(-5, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}


