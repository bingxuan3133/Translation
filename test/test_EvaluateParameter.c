#include "unity.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include "mock_Token.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_evaluate1to2parameter_should_pass_parameter_from_rawString_to_argument () {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10" , .startIndex = 6, .length = 4};
	shuntingYard_ExpectAndReturn(&tempCharArray[0], 0x10);
	argument = evaluate1to2parameter(&parameter);
	
	TEST_ASSERT_NOT_NULL(argument);
	//TEST_ASSERT_EQUAL(10, argument->operand1);
}
