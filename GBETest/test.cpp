#include "pch.h"
#include "InstructionTests.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  ASSERT_EQ(1, 1);
}

TEST_F(InstructionTests, CP_d8_flagTest01) {

	// Set up code and conditions
	CPU->reg_A = 23;
	//   Opcode: CP_d8, d8: dec. 15
	uint8_t testCode[] = {0xFE, 0x0F};
	//   Put into memory
	memcpy(CPU->memory, testCode, sizeof(testCode));

	// Run CPU
	CPU->cycle(); 

	// Was it correct ?
	ASSERT_EQ((uint8_t)CPU->reg_F, (uint8_t)0b01000000);

}