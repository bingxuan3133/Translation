#include "unity.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include "mock_Token.h"
#include <malloc.h>
#include "Error.h"
#include "CException.h"

extern Error exception;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_isDelimiter_should_return_1_if_it_is_a_comment() {
	String subString = {.rawString = ";comment" , .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_a_comment() {
	String subString = {.rawString = ",comment" , .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_isDelimiter_should_return_1_if_it_is_a_comment_with_space() {
	String subString = {.rawString = ";   comment" , .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_a_comment_with_space() {
	String subString = {.rawString = ",   comment" , .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_isDelimiter_should_return_1_if_it_is_delimited_by_a_comma() {
	String subString = {.rawString = ",comment" , .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_delimited_by_a_comma() {
	String subString = {.rawString = ";comment" , .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_isDelimiter_should_return_1_if_it_is_delimited_by_a_comma_with_space_in_between() {
	String subString = {.rawString = ",   comment" , .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_delimited_by_a_comma_with_space_in_between() {
	String subString = {.rawString = ";   comment" , .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(0, result);
}

// Tests for evalueate1to2parameter
void test_evaluate1to2parameter_should_pass_one_parameter_from_rawString_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10" , .startIndex = 6, .length = 4};
	String subString1 = {.rawString = "movwf 0x10" , .startIndex = 6, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate1to2parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(-1, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to2parameter_should_pass_two_parameter_from_rawString_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10, ACCESS" , .startIndex = 6, .length = 12};
	String subString1 = {.rawString = "movwf 0x10, ACCESS" , .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10, ACCESS" , .startIndex = 12, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, ACCESS);

	Try {
		argument = evaluate1to2parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to2parameter_should_pass_one_parameter_with_comment_from_rawString_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10; comment" , .startIndex = 6, .length = 14};
	String subString1 = {.rawString = "movwf 0x10; comment" , .startIndex = 6, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate1to2parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(-1, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to2parameter_should_pass_two_parameter_with_comment_from_rawString_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10, ACCESS; comment" , .startIndex = 6, .length = 21};
	String subString1 = {.rawString = "movwf 0x10, ACCESS; comment" , .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10, ACCESS; comment" , .startIndex = 12, .length = 6};
	String subString3 = {.rawString = "movwf 0x10, ACCESS; comment" , .startIndex = 18, .length = 8};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		argument = evaluate1to2parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to2parameter_should_throw_an_exception_when_there_is_no_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf" , .startIndex = 5, .length = 0};

	Try {
		argument = evaluate1to2parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to2parameter_should_throw_an_exception_when_there_is_missing_first_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf , ACCESS" , .startIndex = 6, .length = 8};

	Try {
		argument = evaluate1to2parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to2parameter_should_throw_an_exception_when_there_is_a_comma_but_missing_second_argument() {
printf("THis tESt");
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10," , .startIndex = 6, .length = 5};
	String subString1 = {.rawString = "movwf 0x10," , .startIndex = 6, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate1to2parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to2parameter_should_throw_an_exception_when_there_is_three_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10, ACCESS, comment" , .startIndex = 6, .length = 21};
	String subString1 = {.rawString = "movwf 0x10, ACCESS, comment" , .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10, ACCESS, comment" , .startIndex = 12, .length = 6};
	String subString3 = {.rawString = "movwf 0x10, ACCESS, comment" , .startIndex = 18, .length = 8};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		argument = evaluate1to2parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

// Tests for 1to3parameter