#pragma once
#include "inst.h"

class cpu
{
	uint8_t reg_A;

/*	Zero Flag(Z) :
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
	uint8_t reg_F;
	uint8_t reg_B;
	uint8_t reg_C;
	uint8_t reg_D;
	uint8_t reg_E;
	uint8_t reg_H;
	uint8_t reg_L;
	uint16_t reg_sp;
	uint16_t reg_pc;

};

