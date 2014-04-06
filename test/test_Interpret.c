#include "unity.h"
#include "Interpret.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include "Error.h"
#include "mock_Token.h"
#include "mock_ReadFile.h"
#include "CException.h"

extern Error exception;

void setUp(void) {}

void tearDown(void) {}

void test_interpret_given_movwf_0x10_ACCESS_should_return_the_correct_bytecode(void) {
	String instruction = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 0, .length = 19};
	String subString1 = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 13, .length = 6};
	Bytecode bytecode;
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		bytecode = interpret(&instruction);
	} Catch (exception) {
		TEST_FAIL_MESSAGE("should not throw an exception");
	}
	
	TEST_ASSERT_EQUAL(MOVWF, bytecode.opcode);
	TEST_ASSERT_EQUAL(0x10, bytecode.operand1);
	TEST_ASSERT_EQUAL(ACCESS, bytecode.operand2);
	TEST_ASSERT_EQUAL(-1, bytecode.operand3);
}

void test_interpret_addwf_0x10_ACCESS_should_return_the_correct_bytecode(void) {
	String instruction = {.rawString = "addwf 0x10 , ACCESS", .startIndex = 0, .length = 19};
	String subString1 = {.rawString = "addwf 0x10 , ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10 , ACCESS", .startIndex = 13, .length = 6};
	Bytecode bytecode;
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		bytecode = interpret(&instruction);
	} Catch (exception) {
		TEST_FAIL_MESSAGE("should not throw an exception");
	}
	
	TEST_ASSERT_EQUAL(ADDWF, bytecode.opcode);
	TEST_ASSERT_EQUAL(0x10, bytecode.operand1);
	TEST_ASSERT_EQUAL(ACCESS, bytecode.operand2);
	TEST_ASSERT_EQUAL(-1, bytecode.operand3);
}

void test_interpret_addwf_0x10_f_ACCESS_should_return_the_correct_bytecode(void) {
	String instruction = {.rawString = "addwf 0x10 , f , ACCESS", .startIndex = 0, .length = 23};
	String subString1 = {.rawString = "addwf 0x10 , f , ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "addwf 0x10 , f , ACCESS", .startIndex = 17, .length = 6};
	Bytecode bytecode;

	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	Try {
		bytecode = interpret(&instruction);
	} Catch (exception) {
		TEST_FAIL_MESSAGE("should not throw an exception");
	}
	
	TEST_ASSERT_EQUAL(ADDWF, bytecode.opcode);
	TEST_ASSERT_EQUAL(0x10, bytecode.operand1);
	TEST_ASSERT_EQUAL(1, bytecode.operand2);
	TEST_ASSERT_EQUAL(ACCESS, bytecode.operand3);
}

void test_interpret_btg_0x10_7_should_return_the_correct_bytecode(void) {
	String instruction = {.rawString = "btg 0x10 , 7", .startIndex = 0, .length = 12};
	String subString1 = {.rawString = "btg 0x10 , 7", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "btg 0x10 , 7", .startIndex = 11, .length = 1};
	Bytecode bytecode;

	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, 7);
	
	Try {
		bytecode = interpret(&instruction);
	} Catch (exception) {
		TEST_FAIL_MESSAGE("should not throw an exception");
	}
	
	TEST_ASSERT_EQUAL(BTG, bytecode.opcode);
	TEST_ASSERT_EQUAL(0x10, bytecode.operand1);
	TEST_ASSERT_EQUAL(7, bytecode.operand2);
	TEST_ASSERT_EQUAL(-1, bytecode.operand3);
}

void test_interpret_btf_0x10_7_should_throw_INVALID_OPCODE(void) {
	String instruction = {.rawString = "btf 0x10 , 7", .startIndex = 0, .length = 12};
	String subString1 = {.rawString = "btf 0x10 , 7", .startIndex = 4, .length = 4};
	String subString2 = {.rawString = "btf 0x10 , 7", .startIndex = 11, .length = 1};
	Bytecode bytecode;
	
	Try {
		bytecode = interpret(&instruction);
		TEST_FAIL_MESSAGE("should throw an exception");
	} Catch (exception) {
		TEST_ASSERT_EQUAL(INVALID_OPCODE, exception);
	}
}

void test_interpret_btg_0x10_should_throw_INVALID_LENGTH_OF_ARGUMENT(void) {
	String instruction = {.rawString = "btg 0x10", .startIndex = 0, .length = 8};
	String subString1 = {.rawString = "btg 0x10", .startIndex = 4, .length = 4};
	Bytecode bytecode;
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	
	Try {
		bytecode = interpret(&instruction);
		TEST_FAIL_MESSAGE("should throw an exception");
	} Catch (exception) {
		TEST_ASSERT_EQUAL(INVALID_LENGTH_OF_ARGUMENT, exception);
	}
}


void test_interpretAll_should_(void) {
	Bytecode programCode[100];
	
	char *ten = "movwf 0x10";
	char *twenty = "movwf 0x20";
	
	String subString1 = {.rawString = ten, .startIndex = 0, .length = 10};
	String subString2 = {.rawString = twenty, .startIndex = 0, .length = 10};
	String subString3 = {.rawString = ten, .startIndex = 6, .length = 4};
	String subString4 = {.rawString = twenty, .startIndex = 6, .length = 4};
	
	readLine_ExpectAndReturn(&subString1);
	evaluate_ExpectAndReturn(&subString3, 0x10);
	
	readLine_ExpectAndReturn(&subString2);
	evaluate_ExpectAndReturn(&subString4, 0x20);
	
	readLine_ExpectAndReturn(NULL);
	
	Try {
		interpretAll(&programCode[0]);
	} Catch (exception) {
		TEST_FAIL_MESSAGE("should not throw an exception");
	}
	
	TEST_ASSERT_EQUAL(MOVWF, programCode[0].opcode);
	TEST_ASSERT_EQUAL(0x10, programCode[0].operand1);
	TEST_ASSERT_EQUAL(-1, programCode[0].operand2);
	TEST_ASSERT_EQUAL(-1, programCode[0].operand3);

	TEST_ASSERT_EQUAL(MOVWF, programCode[1].opcode);
	TEST_ASSERT_EQUAL(0x20, programCode[1].operand1);
	TEST_ASSERT_EQUAL(-1, programCode[1].operand2);
	TEST_ASSERT_EQUAL(-1, programCode[1].operand3);
}

