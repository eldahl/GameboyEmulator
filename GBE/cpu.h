#pragma once
#include <cstdint>
#include "inst.h"

class cpu {
public:

	cpu(uint8_t*, size_t);

	uint8_t read();
	void cycle();
	int opcode(uint8_t);

	void printRegisters(); //DEBUG

	// Cartridge
	size_t cartSize = 0;
	uint8_t* cart = NULL;
	
	uint8_t memory[0xFFFF];
	
	// Registers
	uint8_t reg_A = NULL;
	uint8_t reg_B = NULL;
	uint8_t reg_C = NULL;
	uint8_t reg_D = NULL;
	uint8_t reg_E = NULL;
	uint8_t reg_H = NULL;
	uint8_t reg_L = NULL;
	
	uint8_t reg_F = NULL;
	/*
	-== F register ==-
	Zero Flag(Z) :
		This bit is set when the result of a math operation
		is zero or two values match when using the CP
		instruction.

	Subtract Flag (N):
		This bit is set if a subtraction was performed in the
		last math instruction.

	Half Carry Flag (H):
		This bit is set if a carry occurred from the lower
		nibble in the last math operation.

	Carry Flag (C):
		This bit is set if a carry occurred from the last
		math operation or if register A is the smaller value
		when executing the CP instruction. */

	// Flags
	uint8_t getZFlag();
	uint8_t getNFlag();
	uint8_t getHFlag();
	uint8_t getCFlag();

	// Get pointer to memory location
	uint8_t* getMemRef(uint16_t addr);

	// Stack Pointer and Program Counter
	uint16_t sp = NULL;
	uint16_t pc = NULL;

private:
	bool booted = false;

	// Flags
	void setZFlag(uint8_t);
	void setNFlag(uint8_t);
	void setHFlag(uint8_t);
	void setCFlag(uint8_t);
};

