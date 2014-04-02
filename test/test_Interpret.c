#include "unity.h"
#include "Interpret.h"
#include "EvaluateParameter.h"
#include "StringObject.h"
#include "mock_Token.h"


void setUp(void) {}

void tearDown(void) {}

void test_interpret_should_interpret_an_instruction_and_return_its_bytecode(void) {
	String instruction = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 0, .length = 19};
	String subString1 = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 6, .length = 4};
	String subString2 = {.rawString = "movwf 0x10 , ACCESS", .startIndex = 13, .length = 6};
	Bytecode bytecode;
	
	evaluate_ExpectAndReturn(&subString1, 0x10);
	evaluate_ExpectAndReturn(&subString2, ACCESS);
	
	bytecode = interpret(&instruction);
	
	TEST_ASSERT_EQUAL(MOVWF, bytecode.opcode);
	TEST_ASSERT_EQUAL(0x10, bytecode.operand1);
	TEST_ASSERT_EQUAL(ACCESS, bytecode.operand2);
	TEST_ASSERT_EQUAL(-1, bytecode.operand3);
}
