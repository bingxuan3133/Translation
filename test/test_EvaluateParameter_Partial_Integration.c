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

// Tests for isDelimiter
void test_isDelimiter_should_return_1_if_it_is_a_comment() {
	String subString = {.rawString = ";comment", .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_a_comment() {
	String subString = {.rawString = ",comment", .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_isDelimiter_should_return_1_if_it_is_a_comment_with_space() {
	String subString = {.rawString = ";   comment", .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_a_comment_with_space() {
	String subString = {.rawString = ",   comment", .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ';');
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_isDelimiter_should_return_1_if_it_is_delimited_by_a_comma() {
	String subString = {.rawString = ",comment", .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_delimited_by_a_comma() {
	String subString = {.rawString = ";comment", .startIndex = 1, .length = 8};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_isDelimiter_should_return_1_if_it_is_delimited_by_a_comma_with_space_in_between() {
	String subString = {.rawString = ",   comment", .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(1, result);
}

void test_isDelimiter_should_return_0_if_it_is_not_delimited_by_a_comma_with_space_in_between() {
	String subString = {.rawString = ";   comment", .startIndex = 4, .length = 11};
	int result = isDelimiter(&subString, ',');
	
	TEST_ASSERT_EQUAL(0, result);
}

// Tests for evalueate1to2parameter
void test_evaluate1to2parameter_should_parse_one_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10", .startIndex = 6, .length = 4};
	String subString1 = {.rawString = "movwf 0x10", .startIndex = 6, .length = 4};
	
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

void test_evaluate1to2parameter_should_parse_two_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10, ACCESS", .startIndex = 6, .length = 12};
	String subString1 = {.rawString = "movwf 0x10, ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10, ACCESS", .startIndex = 12, .length = 6};
	
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

void test_evaluate1to2parameter_should_parse_two_parameter_to_argument_without_space_sensetivity() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 6, .length = 13};
	String subString1 = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 13, .length = 6};
	
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

void test_evaluate1to2parameter_should_parse_one_parameter_with_comment_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10; comment", .startIndex = 6, .length = 14};
	String subString1 = {.rawString = "movwf 0x10; comment", .startIndex = 6, .length = 4};
	
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

void test_evaluate1to2parameter_should_parse_two_parameter_with_comment_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10, ACCESS; comment", .startIndex = 6, .length = 21};
	String subString1 = {.rawString = "movwf 0x10, ACCESS; comment", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10, ACCESS; comment", .startIndex = 12, .length = 6};
	String subString3 = {.rawString = "movwf 0x10, ACCESS; comment", .startIndex = 18, .length = 8};
	
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
	String parameter = {.rawString = "movwf", .startIndex = 5, .length = 0};

	Try {
		argument = evaluate1to2parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to2parameter_should_throw_an_exception_when_the_first_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "movwf , ACCESS", .startIndex = 6, .length = 8};

	Try {
		argument = evaluate1to2parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to2parameter_should_throw_an_exception_when_there_is_a_comma_but_the_second_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "movwf 0x10,", .startIndex = 6, .length = 5};
	String subString1 = {.rawString = "movwf 0x10,", .startIndex = 6, .length = 4};
	
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
	String parameter = {.rawString = "movwf 0x10, ACCESS, comment", .startIndex = 6, .length = 21};
	String subString1 = {.rawString = "movwf 0x10, ACCESS, comment", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10, ACCESS, comment", .startIndex = 12, .length = 6};
	
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
void test_evaluate1to3parameter_should_parse_one_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10", .startIndex = 6, .length = 4};
	String subString1 = {.rawString = "addwf 0x10", .startIndex = 6, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(-1, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_parse_two_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, ACCESS", .startIndex = 6, .length = 12};
	String subString1 = {.rawString = "addwf 0x10, ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, ACCESS", .startIndex = 12, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, ACCESS);

	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_parse_three_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, WREG, ACCESS", .startIndex = 6, .length = 18};
	String subString1 = {.rawString = "addwf 0x10, WREG, ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, WREG, ACCESS", .startIndex = 12, .length = 4};
	String subString3 = {.rawString = "addwf 0x10, WREG, ACCESS", .startIndex = 18, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, WREG);
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(WREG, argument->operand2);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_parse_one_parameter_with_comment_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10;   comment", .startIndex = 6, .length = 15};
	String subString1 = {.rawString = "addwf 0x10;   comment", .startIndex = 6, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(-1, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_parse_two_parameter_with_comment_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, ACCESS; comment", .startIndex = 6, .length = 21};
	String subString1 = {.rawString = "addwf 0x10, ACCESS; comment", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, ACCESS; comment", .startIndex = 12, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_parse_three_parameter_with_comment_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, WREG, ACCESS; comment", .startIndex = 6, .length = 27};
	String subString1 = {.rawString = "addwf 0x10, WREG, ACCESS; comment", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, WREG, ACCESS; comment", .startIndex = 12, .length = 4};
	String subString3 = {.rawString = "addwf 0x10, WREG, ACCESS; comment", .startIndex = 18, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, WREG);
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(WREG, argument->operand2);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_parse_three_parameter_with_unconsistent_space_properly() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10 , WREG , ACCESS ; comment", .startIndex = 6, .length = 30};
	String subString1 = {.rawString = "addwf 0x10 , WREG , ACCESS ; comment", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10 , WREG , ACCESS ; comment", .startIndex = 13, .length = 4};
	String subString3 = {.rawString = "addwf 0x10 , WREG , ACCESS ; comment", .startIndex = 20, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, WREG);
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(WREG, argument->operand2);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand3);
	
	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_there_is_no_any_argument() {
	Argument *argument;
	String parameter = {.rawString = "addwf", .startIndex = 5, .length = 0};
	
	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}

	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_there_is_only_comment() {
	Argument *argument;
	String parameter = {.rawString = "addwf ; comment", .startIndex = 6, .length = 9};
	
	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}

	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_the_first_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "addwf , ACCESS", .startIndex = 6, .length = 8};

	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}

	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_there_is_a_comma_but_the_second_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10,", .startIndex = 6, .length = 5};
	String subString1 = {.rawString = "addwf 0x10,", .startIndex = 6, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_there_is_a_comma_but_the_third_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, ACCESS,", .startIndex = 6, .length = 13};
	String subString1 = {.rawString = "addwf 0x10, ACCESS,", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, ACCESS,", .startIndex = 12, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_there_is_a_comma_after_three_arguments() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, WREG, ACCESS,", .startIndex = 6, .length = 24};
	String subString1 = {.rawString = "addwf 0x10, WREG, ACCESS,", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, WREG, ACCESS,", .startIndex = 12, .length = 4};
	String subString3 = {.rawString = "addwf 0x10, WREG, ACCESS,", .startIndex = 18, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, WREG);
	
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate1to3parameter_should_throw_an_exception_when_there_is_four_arguments() {
	Argument *argument;
	String parameter = {.rawString = "addwf 0x10, WREG, ACCESS, hihi", .startIndex = 6, .length = 24};
	String subString1 = {.rawString = "addwf 0x10, WREG, ACCESS, hihi", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10, WREG, ACCESS, hihi", .startIndex = 12, .length = 4};
	String subString3 = {.rawString = "addwf 0x10, WREG, ACCESS, hihi", .startIndex = 18, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, WREG);
	
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate1to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

// Tests for 2to3parameter
void test_evaluate2to3parameter_should_parse_two_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10, 0", .startIndex = 4, .length = 7};
	String subString1 = {.rawString = "bcf 0x10, 0", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "bcf 0x10, 0", .startIndex = 10, .length = 1};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, 0);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");	
	}
	
	TEST_ASSERT_NOT_NULL(argument);	
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(0, argument->operand2);
	TEST_ASSERT_EQUAL(-1, argument->operand3);
}

void test_evaluate2to3parameter_should_parse_three_parameter_to_argument() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10, 0, ACCESS", .startIndex = 4, .length = 15};
	String subString1 = {.rawString = "bcf 0x10, 0, ACCESS", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "bcf 0x10, 0, ACCESS", .startIndex = 10, .length = 1};
	String subString3 = {.rawString = "bcf 0x10, 0, ACCESS", .startIndex = 13, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, 0);
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
	} Catch(exception) {
		TEST_FAIL_MESSAGE("Should not throw exception");
	}
	
	TEST_ASSERT_NOT_NULL(argument);
	TEST_ASSERT_EQUAL(0x10, argument->operand1);
	TEST_ASSERT_EQUAL(0, argument->operand2);
	TEST_ASSERT_EQUAL(ACCESS, argument->operand3);
	
	free(argument);
}


void test_evaluate2to3parameter_should_throw_an_exception_when_there_is_no_any_argument() {
	Argument *argument;
	String parameter = {.rawString = "bcf", .startIndex = 3, .length = 0};
	
	Try {
		argument = evaluate2to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}

	free(argument);
}

void test_evaluate2to3parameter_should_throw_an_exception_when_there_is_only_one_argument() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10", .startIndex = 4, .length = 4};
	String subString1 = {.rawString = "bcf 0x10", .startIndex = 4, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}
	
	free(argument);
}

void test_evaluate2to3parameter_should_throw_an_exception_when_there_is_a_comma_but_the_first_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10,", .startIndex = 4, .length = 4};
	String subString1 = {.rawString = "bcf 0x10,", .startIndex = 4, .length = 4};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}
	
	free(argument);
}

void test_evaluate2to3parameter_should_throw_an_exception_when_there_is_a_comma_but_the_second_argument_is_missing() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10, 0,", .startIndex = 4, .length = 8};
	String subString1 = {.rawString = "bcf 0x10, 0,", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "bcf 0x10, 0,", .startIndex = 10, .length = 1};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, 0);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);
	}
	
	free(argument);
}

void test_evaluate2to3parameter_should_throw_an_exception_when_there_is_comma_after_three_arguments() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10, 0, ACCESS,", .startIndex = 4, .length = 16};
	String subString1 = {.rawString = "bcf 0x10, 0, ACCESS,", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "bcf 0x10, 0, ACCESS,", .startIndex = 10, .length = 1};
	String subString3 = {.rawString = "bcf 0x10, 0, ACCESS,", .startIndex = 13, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, WREG);
	
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}

void test_evaluate2to3parameter_should_throw_an_exception_when_there_is_four_arguments() {
	Argument *argument;
	String parameter = {.rawString = "bcf 0x10, 0, ACCESS, hihi", .startIndex = 4, .length = 21};
	String subString1 = {.rawString = "bcf 0x10, 0, ACCESS, hihi", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "bcf 0x10, 0, ACCESS, hihi", .startIndex = 10, .length = 1};
	String subString3 = {.rawString = "bcf 0x10, 0, ACCESS, hihi", .startIndex = 13, .length = 6};
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	evaluate_ExpectAndReturn(&subString2, WREG);
	
	evaluate_ExpectAndReturn(&subString3, ACCESS);
	
	Try {
		argument = evaluate2to3parameter(&parameter);
		TEST_FAIL_MESSAGE("Should throw an exception");
	} Catch(exception) {
		TEST_ASSERT_EQUAL(INVALID_ARGUMENT, exception);		
	}
	
	free(argument);
}











