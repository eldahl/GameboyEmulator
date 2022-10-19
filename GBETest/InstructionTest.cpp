#include "pch.h"
#include "InstructionTests.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  ASSERT_EQ(1, 1);
}

#pragma region CP_d8 | 0xFE | 254

/*  Tests whether 23 - 15 triggers the half carry flag in the F register of the CPU.
	The half carry flag should be triggered when bit 3 borrows from bit 4. */
TEST_F(InstructionTests, CP_d8_flagTest01) {

	// Set up code and conditions
	CPU->reg_A = 23;
	//   Opcode: CP_d8, d8: decimal 15
	uint8_t testCode[] = { 0xFE, 0x0F };
	//   Put into memory
	memcpy(CPU->memory, testCode, sizeof(testCode));

	// Run CPU
	CPU->cycle();

	// Was it correct ?
	ASSERT_EQ((uint8_t)CPU->reg_F, (uint8_t)0b01000000);

}

/*  Tests whether 23 - 8 triggers the half carry flag in the F register of the CPU.
	The half carry flag should be triggered when bit 3 borrows from bit 4. */
TEST_F(InstructionTests, CP_d8_flagTest02) {

	// Set up code and conditions
	CPU->reg_A = 23;
	//   Opcode: CP_d8, d8: decimal 8
	uint8_t testCode[] = { 0xFE, 0x08 };
	//   Put into memory
	memcpy(CPU->memory, testCode, sizeof(testCode));

	// Run CPU
	CPU->cycle();

	// Was it correct ?
	ASSERT_EQ((uint8_t)CPU->reg_F, (uint8_t)0b01000000);

}

/*  Tests whether 1 - 1 triggers the zero flag, and also that the half carry flag is not triggered, in the F register of the CPU.
	The half carry flag should be triggered when bit 3 borrows from bit 4. */
TEST_F(InstructionTests, CP_d8_flagTest03) {

	// Set up code and conditions
	CPU->reg_A = 1;
	//   Opcode: CP_d8, d8: decimal 1
	uint8_t testCode[] = { 0xFE, 0x01 };
	//   Put into memory
	memcpy(CPU->memory, testCode, sizeof(testCode));

	// Run CPU
	CPU->cycle();

	// Was it correct ?
	ASSERT_EQ((uint8_t)CPU->reg_F, (uint8_t)0b11100000);

}

/*  Tests whether 15 - 23 triggers the half carry flag in the F register of the CPU.
	The half carry flag should be triggered when bit 3 borrows from bit 4. */
TEST_F(InstructionTests, CP_d8_flagTest04) {

	// Set up code and conditions
	CPU->reg_A = 15;
	//   Opcode: CP_d8, d8: decimal 23
	uint8_t testCode[] = { 0xFE, 0x17 };
	//   Put into memory
	memcpy(CPU->memory, testCode, sizeof(testCode));

	// Run CPU
	CPU->cycle();

	// Was it correct ?
	ASSERT_EQ((uint8_t)CPU->reg_F, (uint8_t)0b01110000);

}

/*  Tests whether 8 - 23 triggers the half carry flag in the F register of the CPU.
	The half carry flag should be triggered when bit 3 borrows from bit 4. */
TEST_F(InstructionTests, CP_d8_flagTest05) {

	// Set up code and conditions
	CPU->reg_A = 8;
	//   Opcode: CP_d8, d8: decimal 23
	uint8_t testCode[] = { 0xFE, 0x17 };
	//   Put into memory
	memcpy(CPU->memory, testCode, sizeof(testCode));

	// Run CPU
	CPU->cycle();

	// Was it correct ?
	ASSERT_EQ((uint8_t)CPU->reg_F, (uint8_t)0b01110000);

}

#pragma endregion