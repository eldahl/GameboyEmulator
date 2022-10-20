#include "cpu.h"
#include <iostream>
#include <bitset>
#include <iomanip>

uint8_t BootDMG[] = {
	                                         //
		0x31,0xFE,0xFF,0xAF,0x21,0xFF,0x9F,0x32,0xCB,0x7C,0x20,0xFB,0x21,0x26,0xFF,0x0E, 
		0x11,0x3E,0x80,0x32,0xE2,0x0C,0x3E,0xF3,0xE2,0x32,0x3E,0x77,0x77,0x3E,0xFC,0xE0,
		0x47,0x11,0x04,0x01,0x21,0x10,0x80,0x1A,0xCD,0x95,0x00,0xCD,0x96,0x00,0x13,0x7B, //
		0xFE,0x34,0x20,0xF3,0x11,0xD8,0x00,0x06,0x08,0x1A,0x13,0x22,0x23,0x05,0x20,0xF9,
		0x3E,0x19,0xEA,0x10,0x99,0x21,0x2F,0x99,0x0E,0x0C,0x3D,0x28,0x08,0x32,0x0D,0x20,
		0xF9,0x2E,0x0F,0x18,0xF3,0x67,0x3E,0x64,0x57,0xE0,0x42,0x3E,0x91,0xE0,0x40,0x04,
		0x1E,0x02,0x0E,0x0C,0xF0,0x44,0xFE,0x90,0x20,0xFA,0x0D,0x20,0xF7,0x1D,0x20,0xF2,
		0x0E,0x13,0x24,0x7C,0x1E,0x83,0xFE,0x62,0x28,0x06,0x1E,0xC1,0xFE,0x64,0x20,0x06,
		0x7B,0xE2,0x0C,0x3E,0x87,0xE2,0xF0,0x42,0x90,0xE0,0x42,0x15,0x20,0xD2,0x05,0x20,
		0x4F,0x16,0x20,0x18,0xCB,0x4F,0x06,0x04,0xC5,0xCB,0x11,0x17,0xC1,0xCB,0x11,0x17,
	    0x05,0x20,0xF5,0x22,0x23,0x22,0x23,0xC9,0xCE,0xED,0x66,0x66,0xCC,0x0D,0x00,0x0B, // <<----
		0x03,0x73,0x00,0x83,0x00,0x0C,0x00,0x0D,0x00,0x08,0x11,0x1F,0x88,0x89,0x00,0x0E,
		0xDC,0xCC,0x6E,0xE6,0xDD,0xDD,0xD9,0x99,0xBB,0xBB,0x67,0x63,0x6E,0x0E,0xEC,0xCC,
		0xDD,0xDC,0x99,0x9F,0xBB,0xB9,0x33,0x3E,0x3C,0x42,0xB9,0xA5,0xB9,0xA5,0x42,0x3C,
		0x21,0x04,0x01,0x11,0xA8,0x00,0x1A,0x13,0xBE,0x20,0xFE,0x23,0x7D,0xFE,0x34,0x20,
		0xF5,0x06,0x19,0x78,0x86,0x23,0x05,0x20,0xFB,0x86,0x20,0xFE,0x3E,0x01,0xE0,0x50
};


cpu::cpu(uint8_t* cart, size_t cart_size) {
	pc = 0x0000;
	memset(memory, 0, sizeof(memory));
	memcpy(memory, cart, cart_size);
	memcpy(memory, BootDMG, 256);
	this->cart = cart;
	this->cartSize = cart_size;
}

void cpu::printRegisters() {
	std::cout << "A: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_A << " - " << std::bitset<8>(reg_A) << std::endl;
	std::cout << "B: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_B << " - " << std::bitset<8>(reg_B) << std::endl;
	std::cout << "C: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_C << " - " << std::bitset<8>(reg_C) << std::endl;
	std::cout << "D: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_D << " - " << std::bitset<8>(reg_D) << std::endl;
	std::cout << "E: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_E << " - " << std::bitset<8>(reg_E) << std::endl;
	std::cout << "H: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_H << " - " << std::bitset<8>(reg_H) << std::endl;
	std::cout << "L: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_L << " - " << std::bitset<8>(reg_L) << std::endl;
	std::cout << "F: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)reg_F << " - " << std::bitset<8>(reg_F) << std::endl;
}

void cpu::setZFlag(uint8_t val) {
	if (val != 0 && val != 1) {
		std::cout << "Wrong value given for setZFlag" << std::endl;
		return;
	}
	if (val == 1)
		reg_F |= 0b10000000;
	else
		reg_F &= 0b01111111;
}
void cpu::setNFlag(uint8_t val) {
	if (val != 0 && val != 1) {
		std::cout << "Wrong value given for setNFlag" << std::endl;
		return;
	}
	if (val == 1)
		reg_F |= 0b01000000;
	else
		reg_F &= 0b10111111;
}
void cpu::setHFlag(uint8_t val) {
	if (val != 0 && val != 1) {
		std::cout << "Wrong value given for setHFlag" << std::endl;
		return;
	}
	if (val == 1)
		reg_F |= 0b00100000;
	else
		reg_F &= 0b11011111;
}
void cpu::setCFlag(uint8_t val) {
	if (val != 0 && val != 1) {
		std::cout << "Wrong value given for setCFlag" << std::endl;
		return;
	}
	if (val == 1)
		reg_F |= 0b00010000;
	else
		reg_F &= 0b11101111;
}
uint8_t cpu::getZFlag() {
	return (reg_F >> 7) & 0x1;
}
uint8_t cpu::getNFlag() {
	return (reg_F >> 6) & 0x1;
}
uint8_t cpu::getHFlag() {
	return (reg_F >> 5) & 0x1;
}
uint8_t cpu::getCFlag() {
	return (reg_F >> 4) & 0x1;
}

uint8_t cpu::read() {
	return memory[pc++];
}

void cpu::cycle() {

	if (pc == 0x100)
		return;

	uint8_t op = read();
	opcode(op);
	
}

void ui(uint8_t op) {
	std::cout << "\nUnimplemented instruction: " << std::endl;
	std::cout << std::hex << (int)op << std::endl;
	while (true);
}

int cpu::opcode(uint8_t opcode) 
{
	std::cout << "PC: " << std::hex << (int)pc-1 << " | ";
	std::cout << "|" << std::hex << (int)opcode << std::dec << "|";
	switch (opcode) {
	case inst::NOP:
	case inst::LD_BC_d16:
	case inst::LD_pBC_A:
		ui(opcode);
	case inst::INC_BC: {
		uint16_t reg = reg_C;
		reg += reg_B << 8;
		reg++;
		reg_C = (uint8_t)reg;
		reg_B = (uint8_t)(reg >> 8);
	} break;
	case inst::INC_B: {
		reg_B++;

		setZFlag(reg_B == 0);
		setNFlag(0);
		setHFlag(((reg_B) & 0xF) == 0xF);
	} break;
	case inst::DEC_B: {
		reg_B--;

		setZFlag(reg_B == 0);
		setNFlag(1);
		setHFlag(!(((reg_B) & 0xF) == 0x0));
	} break;
	case inst::LD_B_d8: {
		reg_B = read();
	} break;
	case inst::RLCA:
	case inst::LD_pa16_SP:
	case inst::ADD_HL_BC:
	case inst::LD_A_pBC:
		ui(opcode);
	case inst::DEC_BC: {
		uint16_t reg = reg_C;
		reg += reg_B << 8;
		reg--;
		reg_C = (uint8_t)reg;
		reg_B = (uint8_t)(reg >> 8); 
	} break;
	/*
	Description:
		Increment register n.
	Use with:
		n = A,B,C,D,E,H,L,(HL)
	Flags affected:
		Z - Set if result is zero.
		N - Reset.
		H - Set if carry from bit 3.
		C - Not affected.*/
	case inst::INC_C: {
		reg_C++;

		setZFlag(reg_C == 0);
		setNFlag(0);
		setHFlag(((reg_C) & 0xF) == 0xF);
	} break;
	/*
	Description:
		Decrement register n.
	Use with:
		n = A,B,C,D,E,H,L,(HL)
	Flags affected:
		Z - Set if reselt is zero.
		N - Set.
		H - Set if no borrow from bit 4.
		C - Not affected.*/
	case inst::DEC_C: {
		reg_C--;

		setZFlag(reg_C == 0);
		setNFlag(1);
		setHFlag(!(((reg_C) & 0xF) == 0x0));
	} break;
	// Load the 8-bit immediate operand d8 into register C.
	case inst::LD_C_d8: {
		reg_C = read();
	} break;
	case inst::RRCA:
	case inst::STOP:
		ui(opcode);
	// Load the 2 bytes of immediate data into register pair DE.
	case inst::LD_DE_d16: {
		reg_E = read();
		reg_D = read();
	} break;
	case inst::LD_pDE_A:
		ui(opcode);
	case inst::INC_DE: {
		uint16_t reg = reg_E;
		reg += reg_D << 8;
		reg++;
		reg_E = (uint8_t)reg;
		reg_D = (uint8_t)(reg >> 8);
	} break;
	case inst::INC_D: {
		reg_D++;

		setZFlag(reg_D == 0);
		setNFlag(0);

		// This is wrong
		setHFlag((reg_D & 0xF) == 0xF);

	} break;
	case inst::DEC_D: {
		reg_D--;

		setZFlag(reg_D == 0);
		setNFlag(1);
		// This is wrong
		setHFlag((reg_D & 0xF) == 0x0);
	} break;
	case inst::LD_D_d8:
		ui(opcode);
	case inst::RLA: {
		uint8_t bit = (reg_A >> 7) & 0x1;
		reg_A = reg_A << 1;

		setZFlag(0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(bit);
	} break;
	// Jump s8 steps from the current address in the program counter(PC). (Jump relative.)
	case inst::JR_s8: {
		int s8 = (signed char)read();
		pc += s8;
	} break;
	case inst::ADD_HL_DE:
		ui(opcode);

		// incomplete
		//setNflag(0);
		//if (((reg_C + 1) & 0xFFF) == 0x0)
			//setHflag(1);
	// Load the 8-bit contents of memory specified by register pair DE into register A.
	case inst::LD_A_pDE: {
		uint16_t addr = reg_E;
		addr += reg_D << 8;
		reg_A = memory[addr];
	} break;
	case inst::DEC_DE: {
		uint16_t reg = reg_E;
		reg += reg_D << 8;
		reg--;
		reg_E = (uint8_t)reg;
		reg_D = (uint8_t)(reg >> 8);
	} break;
	case inst::INC_E: {
		reg_E++;

		setZFlag(reg_E == 0);
		setNFlag(0);

		// This is wrong
		setHFlag((reg_E & 0xF) == 0xF);

	} break;
	case inst::DEC_E: {
		reg_E--;

		setZFlag(reg_E == 0);
		setNFlag(1);
		// This is wrong
		setHFlag((reg_E & 0xF) == 0x0);
	} break;
	case inst::LD_E_d8: {
		reg_E = read();
	} break;
	case inst::RRA:
		ui(opcode);
	// If the Z flag is 0, jump s8 steps from the current address stored in the program counter (PC).
	// If not, the instruction following the current JP instruction is executed (as usual).
	case inst::JR_NZ_s8: {
		int s8 = (signed char)read();
		if (((reg_F >> 7) & 0x01) == 0) {
			pc += s8;
			std::cout << " jumping " << s8 << " steps to address: " << pc;
		}
	} break;
	case inst::LD_HL_d16: {
		uint16_t temp = read();
		temp += read() << 8;
		reg_H = (uint8_t)(temp >> 8);
		reg_L = (uint8_t)temp;
	} break;
	case inst::LD_pHL_PLUS_A: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_A;
		addr++;
		reg_L = addr & 0xFF;
		reg_H = (addr >> 8) & 0xFF;
	} break;
	case inst::INC_HL: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		addr++;
		reg_L = (uint8_t)addr;
		reg_H = (uint8_t)(addr >> 8);
	} break;
	case inst::INC_H: {
		reg_H++;

		setZFlag(reg_H == 0);
		setNFlag(0);

		// This is wrong
		setHFlag((reg_H & 0xF) == 0xF);
	} break;
	case inst::DEC_H: {
		reg_H--;

		setZFlag(reg_H == 0);
		setNFlag(1);
		// This is wrong
		setHFlag((reg_H & 0xF) == 0x0);
	} break;
	case inst::LD_H_d8:
	case inst::DAA:
		ui(opcode);
	case inst::JR_Z_s8: {
		int s8 = (signed char)read();
		if (((reg_F >> 7) & 0x01) == 1) {
			pc += s8;
			//std::cout << "jumping " << s8 << " steps to address: " << pc << std::endl;
		}
	} break;
	case inst::ADD_HL_HL:
	case inst::LD_A_pHL_PLUS:
		ui(opcode);
	case inst::DEC_HL: {
		uint16_t reg = reg_L;
		reg += reg_H << 8;
		reg--;
		reg_L = (uint8_t)reg;
		reg_H = (uint8_t)(reg >> 8);
	} break;
	case inst::INC_L: {
		reg_L++;

		setZFlag(reg_L == 0);
		setNFlag(0);

		// This is wrong
		setHFlag((reg_L & 0xF) == 0xF);
	} break;
	case inst::DEC_L: {
		reg_L--;

		setZFlag(reg_L == 0);
		setNFlag(1);
		// This is wrong
		setHFlag((reg_L & 0xF) == 0x0);
	} break;
	case inst::LD_L_d8:
	case inst::CPL:
	case inst::JR_NC_s8:
		ui(opcode);
	// Load 2 byte immediate data into SP
	// First lower then upper
	case inst::LD_SP_d16: {
		uint16_t temp = read();
		temp += read() << 8;
		sp = temp;
	} break;
	// Store the contents of register A into the memory location specified by register pair HL, 
	// and simultaneously decrement the contents of HL.
	case inst::LD_pHL_MINUS_A: {
		uint16_t addr = reg_H << 8 | reg_L;
		memory[addr] = reg_A;
		addr--;
		reg_H = (uint8_t)(addr >> 8);
		reg_L = (uint8_t)addr;
	} break;
	case inst::INC_SP: {
		sp++;
	} break;
	// Increment the contents of memory specified by register pair HL by 1.
	/*
	Description:
		Increment register n.
	Use with:
		n = A,B,C,D,E,H,L,(HL)
	Flags affected:
		Z - Set if result is zero.
		N - Reset.
		H - Set if carry from bit 3.
		C - Not affected */
	case inst::INC_pHL: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr]++;

		setZFlag(memory[addr] == 0);
		setNFlag(0);
		setHFlag(((memory[addr] - 1) & 0xF) == 0xF);
	} break;
	// Decrement the contents of memory specified by register pair HL by 1.
	/*
	Description:
		Decrement register n.
	Use with:
		n = A,B,C,D,E,H,L,(HL)
	Flags affected:
		Z - Set if reselt is zero.
		N - Set.
		H - Set if no borrow from bit 4.
		C - Not affected.*/
	case inst::DEC_pHL: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr]--;

		setZFlag(memory[addr] == 0);
		setNFlag(1);
		setHFlag(!(((memory[addr]) & 0xF) == 0x0));
	} break;
	case inst::LD_pHL_d8:
	case inst::SCF:
	case inst::JR_C_r8:
	case inst::ADD_HL_SP:
	case inst::LD_A_pHL_MINUS:
		ui(opcode);
	case inst::DEC_SP: {
		sp--;
	} break;
	case inst::INC_A: {
		reg_A++;

		setZFlag(reg_A == 0);
		setNFlag(0);

		// This is wrong
		setHFlag((reg_A & 0xF) == 0xF);
	} break;
	case inst::DEC_A: {
		reg_A--;

		setZFlag(reg_A == 0);
		setNFlag(1);
		// This is wrong
		setHFlag((reg_A & 0xF) == 0x0);
	} break;
		ui(opcode);
	// Load the 8-bit immediate operand d8 into register A.
	case inst::LD_A_d8:	{
		reg_A = read();
	} break;
	case inst::CCF:
	////////////////////////////////////////////////////////////////////////////
	case inst::LD_B_B:
	case inst::LD_B_C:
	case inst::LD_B_D:
	case inst::LD_B_E:
	case inst::LD_B_H:
	case inst::LD_B_L:
	case inst::LD_B_pHL:
	case inst::LD_B_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::LD_C_B:
	case inst::LD_C_C:
	case inst::LD_C_D:
	case inst::LD_C_E:
	case inst::LD_C_H:
	case inst::LD_C_L:
	case inst::LD_C_pHL:
	case inst::LD_C_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::LD_D_B:
	case inst::LD_D_C:
	case inst::LD_D_D:
	case inst::LD_D_E:
	case inst::LD_D_H:
	case inst::LD_D_L:
	case inst::LD_D_pHL:
	case inst::LD_D_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::LD_E_B:
	case inst::LD_E_C:
	case inst::LD_E_D:
	case inst::LD_E_E:
	case inst::LD_E_H:
	case inst::LD_E_L:
	case inst::LD_E_pHL:
	case inst::LD_E_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::LD_H_B:
	case inst::LD_H_C:
	case inst::LD_H_D:
	case inst::LD_H_E:
	case inst::LD_H_H:
	case inst::LD_H_L:
	case inst::LD_H_pHL:
	case inst::LD_H_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::LD_L_B:
	case inst::LD_L_C:
	case inst::LD_L_D:
	case inst::LD_L_E:
	case inst::LD_L_H:
	case inst::LD_L_L:
	case inst::LD_L_pHL:
	case inst::LD_L_A:
	////////////////////////////////////////////////////////////////////////////
	// Store the contents of register N in the memory location specified by register pair HL.
	case inst::LD_pHL_B: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_B;
	} break;
	case inst::LD_pHL_C: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_C;
	} break;
	case inst::LD_pHL_D: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_D;
	} break;
	case inst::LD_pHL_E: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_E;
	} break;
	case inst::LD_pHL_H: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_H;
	} break;
	case inst::LD_pHL_L: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_L;
	} break;
	// Power down CPU until an interrupt occurs. Use this
	// when ever possible to reduce energy consumption.
	/*
	After a HALT instruction is executed, the system clock is stopped and HALT mode is entered. 
	Although the system clock is stopped in this status, the oscillator circuit and LCD controller 
	continue to operate.
	
	In addition, the status of the internal RAM register ports remains unchanged.
	HALT mode is cancelled by an interrupt or reset signal.
	The program counter is halted at the step after the HALT instruction. 
	If both the interrupt request flag and the corresponding interrupt enable flag are set, 
	HALT mode is exited, even if the interrupt master enable flag is not set.
	
	Once HALT mode is cancelled, the program starts from the address indicated by the 
	program counter.
	If the interrupt master enable flag is set, the contents of the program coounter 
	are pushed to the stack and control jumps to the starting address of the interrupt.
	
	If the RESET terminal goes LOW in HALT mode, the mode becomes that of a normal reset.*/
	case inst::HALT:
		ui(opcode);
	// Store the contents of register A in the memory location specified by register pair HL.
	case inst::LD_pHL_A: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_A;
	} break;
	////////////////////////////////////////////////////////////////////////////
	// Load the contents of register n into register A.
	case inst::LD_A_B: {
		reg_A = reg_B;
	} break;
	case inst::LD_A_C: {
		reg_A = reg_C;
	} break;
	case inst::LD_A_D: {
		reg_A = reg_D;
	} break;
	case inst::LD_A_E: {
		reg_A = reg_E;
	} break;
	case inst::LD_A_H: {
		reg_A = reg_H;
	} break;
	case inst::LD_A_L: {
		reg_A = reg_L;
	} break;
	// Load the 8-bit contents of memory specified by register pair HL into register A.
	case inst::LD_A_pHL: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		reg_A = memory[addr];
	} break;
	case inst::LD_A_A: {
		reg_A = reg_A;
	} break;
	////////////////////////////////////////////////////////////////////////////
	case inst::ADD_A_B:
	case inst::ADD_A_C:
	case inst::ADD_A_D:
	case inst::ADD_A_E:
	case inst::ADD_A_H:
	case inst::ADD_A_L:
	case inst::ADD_A_pHL:
	case inst::ADD_A_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::ADC_A_B:
	case inst::ADC_A_C:
	case inst::ADC_A_D:
	case inst::ADC_A_E:
	case inst::ADC_A_H:
	case inst::ADC_A_L:
	case inst::ADC_A_pHL:
	case inst::ADC_A_A:
	////////////////////////////////////////////////////////////////////////////
	/*
	Description:
		Subtract n from A.
	Flags affected:
		Z - Set if result is zero.
		N - Set.
		H - Set if no borrow from bit 4.
		C - Set if no borrow.*/
	case inst::SUB_B: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_B;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (reg_B & 0xf)) < 0x0));
		setCFlag(previousRegAVal > reg_B);
	} break;
	case inst::SUB_C: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_C;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (reg_C & 0xf)) < 0x0));
		setCFlag(previousRegAVal > reg_C);
	} break;
	case inst::SUB_D: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_D;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (reg_D & 0xf)) < 0x0));
		setCFlag(previousRegAVal > reg_D);
	} break;
	case inst::SUB_E: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_E;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (reg_E & 0xf)) < 0x0));
		setCFlag(previousRegAVal > reg_E);
	} break;
	case inst::SUB_H: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_H;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (reg_H & 0xf)) < 0x0));
		setCFlag(previousRegAVal > reg_H);
	} break;
	case inst::SUB_L: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_L;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (reg_L & 0xf)) < 0x0));
		setCFlag(previousRegAVal > reg_L);
	} break;
	case inst::SUB_pHL: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;

		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - memory[addr];

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(!(((previousRegAVal & 0xf) - (memory[addr] & 0xf)) < 0x0));
		setCFlag(previousRegAVal > memory[addr]);
	} break;
	case inst::SUB_A: {
		uint8_t previousRegAVal = reg_A;
		reg_A = reg_A - reg_A;

		setZFlag(reg_A == 0);
		setNFlag(1);
		setHFlag(0);
		setCFlag(0);
	} break;
	////////////////////////////////////////////////////////////////////////////
	case inst::SBC_A_B:
	case inst::SBC_A_C:
	case inst::SBC_A_D:
	case inst::SBC_A_E:
	case inst::SBC_A_H:
	case inst::SBC_A_L:
	case inst::SBC_A_pHL:
	case inst::SBC_A_A:
		ui(opcode);
	////////////////////////////////////////////////////////////////////////////
	// Take the logical AND for each bit of the contents of register n 
	// and the contents of register A, and store the results in register A.
	/*
	Description:
		Logically AND n with A, result in A.
	Use with :
		n = A, B, C, D, E, H, L, (HL), #
	Flags affected :
		Z - Set if result is zero.
		N - Reset.
		H - Set.
		C - Reset. */
	case inst::AND_B: {
		reg_A = reg_B & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	case inst::AND_C: {
		reg_A = reg_C & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	case inst::AND_D: {
		reg_A = reg_D & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	case inst::AND_E: {
		reg_A = reg_E & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	case inst::AND_H: {
		reg_A = reg_H & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	case inst::AND_L: {
		reg_A = reg_L & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
		// Take the logical AND for each bit of the contents of memory specified by register pair HL
		// and the contents of register A, and store the results in register A.
	case inst::AND_pHL: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;

		reg_A = memory[addr] & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	case inst::AND_A: {
		reg_A = reg_A & reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(1);
		setCFlag(0);
	} break;
	////////////////////////////////////////////////////////////////////////////
	// Take the logical exclusive-OR for each bit of the contents of register A
	// and the contents of register A, and store the results in register A.
	/*
	Description:
		Logical exclusive OR n with register A, result in A.
	Use with:
		n = A,B,C,D,E,H,L,(HL),#
	Flags affected:
		Z - Set if result is zero.
		N - Reset.
		H - Reset.
		C - Reset. */
	case inst::XOR_B: {
		reg_A = reg_B ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	case inst::XOR_C: {
		reg_A = reg_C ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	case inst::XOR_D: {
		reg_A = reg_D ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	case inst::XOR_E: {
		reg_A = reg_E ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	case inst::XOR_H: {
		reg_A = reg_H ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	case inst::XOR_L: {
		reg_A = reg_L ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
		// Take the logical exclusive-OR for each bit of the contents of memory 
		// specified by register pair HL and the contents of register A, 
		// and store the results in register A.
	case inst::XOR_pHL: {
		// Get address
		uint16_t addr = reg_L;
		addr += reg_H << 8;

		uint8_t data = memory[addr];
		reg_A = data ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	case inst::XOR_A: {
		reg_A = reg_A ^ reg_A;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(0);
		setCFlag(0);
	} break;
	////////////////////////////////////////////////////////////////////////////
	/*
	Description:
		Logical OR n with register A, result in A.
	Use with:
		n = A,B,C,D,E,H,L,(HL),#
	Flags affected:
		Z - Set if result is zero.
		N - Reset.
		H - Reset.
		C - Reset. */
	case inst::OR_B:
	case inst::OR_C:
	case inst::OR_D:
	case inst::OR_E:
	case inst::OR_H:
	case inst::OR_L:
	case inst::OR_pHL:
	case inst::OR_A:
	////////////////////////////////////////////////////////////////////////////
	/*
	Description:
		Compare A with n. This is basically an A - n
		subtraction instruction but the results are thrown away.
	Use with:
		n = A,B,C,D,E,H,L,(HL),#
	Flags affected:
		Z - Set if result is zero. (Set if A = n.)
		N - Set.
		H - Set if no borrow from bit 4.
		C - Set for no borrow. (Set if A < n.) */
	case inst::CP_B:
	case inst::CP_C:
	case inst::CP_D:
	case inst::CP_E:
	case inst::CP_H:
	case inst::CP_L:
	case inst::CP_pHL:
	case inst::CP_A:
	////////////////////////////////////////////////////////////////////////////
	case inst::RET_NZ:
		ui(opcode);
	case inst::POP_BC: {
		reg_C = memory[sp++];
		reg_B = memory[sp++];

	} break;
	case inst::JP_NZ_a16:
		ui(opcode);
	// Load the 16-bit immediate operand a16 into the program counter (PC). 
	// a16 specifies the address of the subsequently executed instruction.
	case inst::JP_a16: {
		uint16_t addr = read();
		addr += read() << 8;
		pc = addr;
		////////////////////////////////////////////////////////////////////////// unsure
	} break;
	case inst::CALL_NZ_a16:
		ui(opcode);
	/*
	Description:
		Push register pair nn onto stack.
		Decrement Stack Pointer (SP) twice.
	*/
	case inst::PUSH_BC: {
		// Put register pair BC onto stack
		memory[--sp] = reg_B;
		memory[--sp] = reg_C;
	} break;
	/*
	Description:
		Add n to A.
	Use with:
		n = A,B,C,D,E,H,L,(HL),#
	Flags affected:
		Z - Set if result is zero.
		N - Reset.
		H - Set if carry from bit 3.
		C - Set if carry from bit 7. */
	case inst::ADD_A_d8: {
		uint8_t d8 = read();
		uint8_t previousVal = reg_A;
		reg_A = reg_A + d8;

		setZFlag(reg_A == 0);
		setNFlag(0);
		setHFlag(((d8 & 0xf) + (previousVal & 0xf)) & 0x10);
		setCFlag(((d8 & 0xff) + (previousVal & 0xff)) & 0x100);
	} break;
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_00H:
	case inst::RET_Z:
		ui(opcode);
	case inst::RET: {
		uint16_t addr = memory[sp++] << 8;
		addr += memory[sp++];
		pc = addr;
		
		std::cout << "[" << std::hex << addr << std::dec << "]" << " - RET";
	} break;
	case inst::JP_Z_a16:
		ui(opcode);
	// CB Prefix instructions
	case inst::PREFIX_CB: {
		uint8_t op = read();

		std::cout << "|" << std::hex << (int)op << std::dec << "|";
		
		switch (op) {
		/*
		Description:
			Rotate n left. Old bit 7 to Carry flag.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 7 data. */
		case instCB::RLC_B: {
			reg_B = (reg_B << 1) | (reg_B >> 7);

			setZFlag(reg_B == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_B & 0x1);
		} break;
		case instCB::RLC_C: {
			reg_C = (reg_C << 1) | (reg_C >> 7);

			setZFlag(reg_C == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_C & 0x1);
		} break;
		case instCB::RLC_D: {
			reg_D = (reg_D << 1) | (reg_D >> 7);

			setZFlag(reg_D == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_D & 0x1);
		} break;
		case instCB::RLC_E: {
			reg_E = (reg_E << 1) | (reg_E >> 7);

			setZFlag(reg_E == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_E & 0x1);
		} break;
		case instCB::RLC_H: {
			reg_H = (reg_H << 1) | (reg_H >> 7);

			setZFlag(reg_H == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_H & 0x1);
		} break;
		case instCB::RLC_L: {
			reg_L = (reg_L << 1) | (reg_L >> 7);

			setZFlag(reg_L == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_L & 0x1);
		} break;
		case instCB::RLC_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] = (memory[addr] << 1) | (memory[addr] >> 7);

			setZFlag(memory[addr] == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(memory[addr] & 0x1);
		} break;
		case instCB::RLC_A: {
			reg_A = (reg_A << 1) | (reg_A >> 7);

			setZFlag(reg_A == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_A & 0x1);
		} break;
		//////////////////////////////////////
		/*
		Description:
			Rotate n right. Old bit 0 to Carry flag.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 0 data. */
		case instCB::RRC_B: {
			reg_B = (reg_B >> 1) | (reg_B << 7);

			setZFlag(reg_B == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_B & 0x1);
		} break;
		case instCB::RRC_C: {
			reg_C = (reg_C >> 1) | (reg_C << 7);

			setZFlag(reg_C == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_C & 0x1);
		} break;
		case instCB::RRC_D: {
			reg_D = (reg_D >> 1) | (reg_D << 7);

			setZFlag(reg_D == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_D & 0x1);
		} break;
		case instCB::RRC_E: {
			reg_E = (reg_E >> 1) | (reg_E << 7);

			setZFlag(reg_E == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_E & 0x1);
		} break;
		case instCB::RRC_H: {
			reg_H = (reg_H >> 1) | (reg_H << 7);

			setZFlag(reg_H == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_H & 0x1);
		} break;
		case instCB::RRC_L: {
			reg_L = (reg_L >> 1) | (reg_L << 7);

			setZFlag(reg_L == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_L & 0x1);
		} break;
		case instCB::RRC_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] = (memory[addr] >> 1) | (memory[addr] << 7);

			setZFlag(memory[addr] == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(memory[addr] & 0x1);
		} break;
		case instCB::RRC_A: {
			reg_A = (reg_A >> 1) | (reg_A << 7);

			setZFlag(reg_A == 0);
			setNFlag(0);
			setHFlag(0);
			setCFlag(reg_A & 0x1);
		} break;
		//////////////////////////////////////
		/*
		Description:
			Rotate n left through Carry flag.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 7 data. */
		case instCB::RL_B: {
			reg_B = (reg_B << 1) | getCFlag();

			setZFlag(reg_B == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_C: {
			reg_C = (reg_C << 1) | getCFlag();

			setZFlag(reg_C == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_D: {
			reg_D = (reg_D << 1) | getCFlag();

			setZFlag(reg_D == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_E: {
			reg_E = (reg_E << 1) | getCFlag();

			setZFlag(reg_E == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_H: {
			reg_H = (reg_H << 1) | getCFlag();

			setZFlag(reg_H == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_L: {
			reg_L = (reg_L << 1) | getCFlag();

			setZFlag(reg_L == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] = (memory[addr] << 1) | getCFlag();

			setZFlag(memory[addr] == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RL_A: {
			reg_A = (reg_A << 1) | getCFlag();

			setZFlag(reg_A == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		//////////////////////////////////////
		/*
		Description:
			Rotate n right through Carry flag.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 0 data. */
		case instCB::RR_B: {
			reg_B = (reg_B >> 1) | (getCFlag() << 7);

			setZFlag(reg_B == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_C: {
			reg_C = (reg_C >> 1) | (getCFlag() << 7);

			setZFlag(reg_C == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_D: {
			reg_D = (reg_D >> 1) | (getCFlag() << 7);

			setZFlag(reg_D == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_E: {
			reg_E = (reg_E >> 1) | (getCFlag() << 7);

			setZFlag(reg_E == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_H: {
			reg_H = (reg_H >> 1) | (getCFlag() << 7);

			setZFlag(reg_H == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_L: {
			reg_L = (reg_L >> 1) | (getCFlag() << 7);

			setZFlag(reg_L == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] = (memory[addr] >> 1) | (getCFlag() << 7);

			setZFlag(memory[addr] == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::RR_A: {
			reg_A = (reg_A >> 1) | (getCFlag() << 7);

			setZFlag(reg_A == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		//////////////////////////////////////
		/*
		Description:
			Shift n left into Carry. LSB of n set to 0.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 7 data. */
		case instCB::SLA_B: {
			setCFlag((reg_B >> 7) & 0x1);
			reg_B = reg_B << 1;

			setZFlag(reg_B == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_C: {
			setCFlag((reg_C >> 7) & 0x1);
			reg_C = reg_C << 1;

			setZFlag(reg_C == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_D: {
			setCFlag((reg_D >> 7) & 0x1);
			reg_D = reg_D << 1;

			setZFlag(reg_D == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_E: {
			setCFlag((reg_E >> 7) & 0x1);
			reg_E = reg_E << 1;

			setZFlag(reg_E == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_H: {
			setCFlag((reg_H >> 7) & 0x1);
			reg_H = reg_H << 1;

			setZFlag(reg_H == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_L: {
			setCFlag((reg_L >> 7) & 0x1);
			reg_L = reg_L << 1;

			setZFlag(reg_L == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			
			setCFlag((memory[addr] >> 7) & 0x1);
			memory[addr] = memory[addr] << 1;

			setZFlag(memory[addr] == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
		case instCB::SLA_A: {
			setCFlag((reg_A >> 7) & 0x1);
			reg_A = reg_A << 1;

			setZFlag(reg_A == 0);
			setNFlag(0);
			setHFlag(0);
		} break;
			break;
		//////////////////////////////////////
		/*
		Description:
			Shift n right into Carry. MSB doesn't change.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 0 data. */
		case instCB::SRA_B:
		case instCB::SRA_C:
		case instCB::SRA_D:
		case instCB::SRA_E:
		case instCB::SRA_H:
		case instCB::SRA_L:
		case instCB::SRA_pHL:
		case instCB::SRA_A:
			break;
		//////////////////////////////////////
		/*
		Description:
			Swap upper & lower nibles of n.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Reset. */
		case instCB::SWAP_B:
		case instCB::SWAP_C:
		case instCB::SWAP_D:
		case instCB::SWAP_E:
		case instCB::SWAP_H:
		case instCB::SWAP_L:
		case instCB::SWAP_pHL:
		case instCB::SWAP_A:
			break;
		//////////////////////////////////////
		/*
		Description:
			Shift n right into Carry. MSB set to 0.
		Use with:
			n = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if result is zero.
			N - Reset.
			H - Reset.
			C - Contains old bit 0 data. */
		case instCB::SRL_B:
		case instCB::SRL_C:
		case instCB::SRL_D:
		case instCB::SRL_E:
		case instCB::SRL_H:
		case instCB::SRL_L:
		case instCB::SRL_pHL:
		case instCB::SRL_A:
			break;
		//////////////////////////////////////
		// Copy the complement of the contents of bit n in register r
		// to the Z flag of the program status word (PSW).
		/*
		Description:
			Test bit b in register r.
		Use with:
			b = 0 - 7, r = A,B,C,D,E,H,L,(HL)
		Flags affected:
			Z - Set if bit b of register r is 0.
			N - Reset.
			H - Set.
			C - Not affected. */
		case instCB::BIT_0_B: {
			uint8_t bit = reg_B & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_C: {
			uint8_t bit = reg_C & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_D: {
			uint8_t bit = reg_D & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_E: {
			uint8_t bit = reg_E & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_H: {
			uint8_t bit = reg_H & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_L: {
			uint8_t bit = reg_L & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_0_A: {
			uint8_t bit = reg_A & 0b00000001;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		//////////////////////////////////////
		case instCB::BIT_1_B: {
			uint8_t bit = reg_B & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_C: {
			uint8_t bit = reg_C & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_D: {
			uint8_t bit = reg_D & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_E: {
			uint8_t bit = reg_E & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_H: {
			uint8_t bit = reg_H & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_L: {
			uint8_t bit = reg_L & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_1_A: {
			uint8_t bit = reg_A & 0b00000010;
			bit = bit >> 1;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
			//////////////////////////////////////
		case instCB::BIT_2_B: {
			uint8_t bit = reg_B & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_C: {
			uint8_t bit = reg_C & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_D: {
			uint8_t bit = reg_D & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_E: {
			uint8_t bit = reg_E & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_H: {
			uint8_t bit = reg_H & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_L: {
			uint8_t bit = reg_L & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_2_A: {
			uint8_t bit = reg_A & 0b00000100;
			bit = bit >> 2;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
			//////////////////////////////////////
		case instCB::BIT_3_B: {
			uint8_t bit = reg_B & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_C: {
			uint8_t bit = reg_C & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_D: {
			uint8_t bit = reg_D & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_E: {
			uint8_t bit = reg_E & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_H: {
			uint8_t bit = reg_H & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_L: {
			uint8_t bit = reg_L & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_3_A: {
			uint8_t bit = reg_A & 0b00001000;
			bit = bit >> 3;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
			//////////////////////////////////////
		case instCB::BIT_4_B: {
			uint8_t bit = reg_B & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_C: {
			uint8_t bit = reg_C & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_D: {
			uint8_t bit = reg_D & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_E: {
			uint8_t bit = reg_E & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_H: {
			uint8_t bit = reg_H & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_L: {
			uint8_t bit = reg_L & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_4_A: {
			uint8_t bit = reg_A & 0b00010000;
			bit = bit >> 4;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
			//////////////////////////////////////
		case instCB::BIT_5_B: {
			uint8_t bit = reg_B & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_C: {
			uint8_t bit = reg_C & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_D: {
			uint8_t bit = reg_D & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_E: {
			uint8_t bit = reg_E & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_H: {
			uint8_t bit = reg_H & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_L: {
			uint8_t bit = reg_L & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_5_A: {
			uint8_t bit = reg_A & 0b00100000;
			bit = bit >> 5;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
			//////////////////////////////////////
		case instCB::BIT_6_B: {
			uint8_t bit = reg_B & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_C: {
			uint8_t bit = reg_C & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_D: {
			uint8_t bit = reg_D & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_E: {
			uint8_t bit = reg_E & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_H: {
			uint8_t bit = reg_H & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_L: {
			uint8_t bit = reg_L & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_6_A: {
			uint8_t bit = reg_A & 0b01000000;
			bit = bit >> 6;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
			//////////////////////////////////////
		case instCB::BIT_7_B: {
			uint8_t bit = reg_B & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_C: {
			uint8_t bit = reg_C & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_D: {
			uint8_t bit = reg_D & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_E: {
			uint8_t bit = reg_E & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_H: {
			uint8_t bit = reg_H & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_L:
		{
			uint8_t bit = reg_L & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		case instCB::BIT_7_A: {
			uint8_t bit = reg_A & 0b10000000;
			bit = bit >> 7;
			setZFlag(bit == 0);
			setNFlag(0);
			setHFlag(1);
		} break;
		//////////////////////////////////////
		/*
		Description:
			Reset bit b in register r.
		Use with:
			b = 0 - 7, r = A,B,C,D,E,H,L,(HL)
		Flags affected:
			None. */
		case instCB::RES_0_B: {
			reg_B &= 0b11111110;
		} break;
		case instCB::RES_0_C: {
			reg_C &= 0b11111110;
		} break;
		case instCB::RES_0_D: {
			reg_D &= 0b11111110;
		} break;
		case instCB::RES_0_E: {
			reg_E &= 0b11111110;
		} break;
		case instCB::RES_0_H: {
			reg_H &= 0b11111110;
		} break;
		case instCB::RES_0_L: {
			reg_L &= 0b11111110;
		} break;
		case instCB::RES_0_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b11111110;
		} break;
		case instCB::RES_0_A: {
			reg_A &= 0b11111110;
		} break;
		//////////////////////////////////////
		case instCB::RES_1_B: {
			reg_B &= 0b11111101;
		} break;
		case instCB::RES_1_C: {
			reg_C &= 0b11111101;
		} break;
		case instCB::RES_1_D: {
			reg_D &= 0b11111101;
		} break;
		case instCB::RES_1_E: {
			reg_E &= 0b11111101;
		} break;
		case instCB::RES_1_H: {
			reg_H &= 0b11111101;
		} break;
		case instCB::RES_1_L: {
			reg_L &= 0b11111101;
		} break;
		case instCB::RES_1_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b11111101;
		} break;
		case instCB::RES_1_A: {
			reg_A &= 0b11111101;
		} break;
		//////////////////////////////////////
		case instCB::RES_2_B: {
			reg_B &= 0b11111011;
		} break;
		case instCB::RES_2_C: {
			reg_C &= 0b11111011;
		} break;
		case instCB::RES_2_D: {
			reg_D &= 0b11111011;
		} break;
		case instCB::RES_2_E: {
			reg_E &= 0b11111011;
		} break;
		case instCB::RES_2_H: {
			reg_H &= 0b11111011;
		} break;
		case instCB::RES_2_L: {
			reg_L &= 0b11111011;
		} break;
		case instCB::RES_2_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b11111011;
		} break;
		case instCB::RES_2_A: {
			reg_A &= 0b11111011;
		} break;
		//////////////////////////////////////
		case instCB::RES_3_B: {
			reg_B &= 0b11110111;
		} break;
		case instCB::RES_3_C: {
			reg_C &= 0b11110111;
		} break;
		case instCB::RES_3_D: {
			reg_D &= 0b11110111;
		} break;
		case instCB::RES_3_E: {
			reg_E &= 0b11110111;
		} break;
		case instCB::RES_3_H: {
			reg_H &= 0b11110111;
		} break;
		case instCB::RES_3_L: {
			reg_L &= 0b11110111;
		} break;
		case instCB::RES_3_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b11110111;
		} break;
		case instCB::RES_3_A: {
			reg_A &= 0b11110111;
		} break;
		//////////////////////////////////////
		case instCB::RES_4_B: {
			reg_B &= 0b11101111;
		} break;
		case instCB::RES_4_C: {
			reg_C &= 0b11101111;
		} break;
		case instCB::RES_4_D: {
			reg_D &= 0b11101111;
		} break;
		case instCB::RES_4_E: {
			reg_E &= 0b11101111;
		} break;
		case instCB::RES_4_H: {
			reg_H &= 0b11101111;
		} break;
		case instCB::RES_4_L: {
			reg_L &= 0b11101111;
		} break;
		case instCB::RES_4_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b11101111;
		} break;
		case instCB::RES_4_A: {
			reg_A &= 0b11101111;
		} break;
		//////////////////////////////////////
		case instCB::RES_5_B: {
			reg_B &= 0b11011111;
		} break;
		case instCB::RES_5_C: {
			reg_C &= 0b11011111;
		} break;
		case instCB::RES_5_D: {
			reg_D &= 0b11011111;
		} break;
		case instCB::RES_5_E: {
			reg_E &= 0b11011111;
		} break;
		case instCB::RES_5_H: {
			reg_H &= 0b11011111;
		} break;
		case instCB::RES_5_L: {
			reg_L &= 0b11011111;
		} break;
		case instCB::RES_5_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b11011111;
		} break;
		case instCB::RES_5_A: {
			reg_A &= 0b11011111;
		} break;
		//////////////////////////////////////
		case instCB::RES_6_B: {
			reg_B &= 0b10111111;
		} break;
		case instCB::RES_6_C: {
			reg_C &= 0b10111111;
		} break;
		case instCB::RES_6_D: {
			reg_D &= 0b10111111;
		} break;
		case instCB::RES_6_E: {
			reg_E &= 0b10111111;
		} break;
		case instCB::RES_6_H: {
			reg_H &= 0b10111111;
		} break;
		case instCB::RES_6_L: {
			reg_L &= 0b10111111;
		} break;
		case instCB::RES_6_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b10111111;
		} break;
		case instCB::RES_6_A: {
			reg_A &= 0b10111111;
		} break;
		//////////////////////////////////////
		case instCB::RES_7_B: {
			reg_B &= 0b01111111;
		} break;
		case instCB::RES_7_C: {
			reg_C &= 0b01111111;
		} break;
		case instCB::RES_7_D: {
			reg_D &= 0b01111111;
		} break;
		case instCB::RES_7_E: {
			reg_E &= 0b01111111;
		} break;
		case instCB::RES_7_H: {
			reg_H &= 0b01111111;
		} break;
		case instCB::RES_7_L: {
			reg_L &= 0b01111111;
		} break;
		case instCB::RES_7_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] &= 0b01111111;
		} break;
		case instCB::RES_7_A: {
			reg_A &= 0b01111111;
		} break;
		//////////////////////////////////////
		/*
		Description:
			Set bit b in register r.
		Use with:
			b = 0 - 7, r = A,B,C,D,E,H,L,(HL)
		Flags affected:
			None. */
		case instCB::SET_0_B: {
			reg_B |= 0b00000001;
		} break;
		case instCB::SET_0_C: {
			reg_C |= 0b00000001;
		} break;
		case instCB::SET_0_D: {
			reg_D |= 0b00000001;
		} break;
		case instCB::SET_0_E: {
			reg_E |= 0b00000001;
		} break;
		case instCB::SET_0_H: {
			reg_H |= 0b00000001;
		} break;
		case instCB::SET_0_L: {
			reg_L |= 0b00000001;
		} break;
		case instCB::SET_0_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b00000001;
		} break;
		case instCB::SET_0_A: {
			reg_A |= 0b00000001;
		} break;
		//////////////////////////////////////
		case instCB::SET_1_B: {
			reg_B |= 0b00000010;
		} break;
		case instCB::SET_1_C: {
			reg_C |= 0b00000010;
		} break;
		case instCB::SET_1_D: {
			reg_D |= 0b00000010;
		} break;
		case instCB::SET_1_E: {
			reg_E |= 0b00000010;
		} break;
		case instCB::SET_1_H: {
			reg_H |= 0b00000010;
		} break;
		case instCB::SET_1_L: {
			reg_L |= 0b00000010;
		} break;
		case instCB::SET_1_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b00000010;
		} break;
		case instCB::SET_1_A: {
			reg_A |= 0b00000010;
		} break;
			//////////////////////////////////////
		case instCB::SET_2_B: {
			reg_B |= 0b00000100;
		} break;
		case instCB::SET_2_C: {
			reg_C |= 0b00000100;
		} break;
		case instCB::SET_2_D: {
			reg_D |= 0b00000100;
		} break;
		case instCB::SET_2_E: {
			reg_E |= 0b00000100;
		} break;
		case instCB::SET_2_H: {
			reg_H |= 0b00000100;
		} break;
		case instCB::SET_2_L: {
			reg_L |= 0b00000100;
		} break;
		case instCB::SET_2_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b00000100;
		} break;
		case instCB::SET_2_A: {
			reg_A |= 0b00000100;
		} break;
			//////////////////////////////////////
		case instCB::SET_3_B: {
			reg_B |= 0b00001000;
		} break;
		case instCB::SET_3_C: {
			reg_C |= 0b00001000;
		} break;
		case instCB::SET_3_D: {
			reg_D |= 0b00001000;
		} break;
		case instCB::SET_3_E: {
			reg_E |= 0b00001000;
		} break;
		case instCB::SET_3_H: {
			reg_H |= 0b00001000;
		} break;
		case instCB::SET_3_L: {
			reg_L |= 0b00001000;
		} break;
		case instCB::SET_3_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b00001000;
		} break;
		case instCB::SET_3_A: {
			reg_A |= 0b00001000;
		} break;
			//////////////////////////////////////
		case instCB::SET_4_B: {
			reg_B |= 0b00010000;
		} break;
		case instCB::SET_4_C: {
			reg_C |= 0b00010000;
		} break;
		case instCB::SET_4_D: {
			reg_D |= 0b00010000;
		} break;
		case instCB::SET_4_E: {
			reg_E |= 0b00010000;
		} break;
		case instCB::SET_4_H: {
			reg_H |= 0b00010000;
		} break;
		case instCB::SET_4_L: {
			reg_L |= 0b00010000;
		} break;
		case instCB::SET_4_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b00010000;
		} break;
		case instCB::SET_4_A: {
			reg_A |= 0b00010000;
		} break;
			//////////////////////////////////////
		case instCB::SET_5_B: {
			reg_B |= 0b00100000;
		} break;
		case instCB::SET_5_C: {
			reg_C |= 0b00100000;
		} break;
		case instCB::SET_5_D: {
			reg_D |= 0b00100000;
		} break;
		case instCB::SET_5_E: {
			reg_E |= 0b00100000;
		} break;
		case instCB::SET_5_H: {
			reg_H |= 0b00100000;
		} break;
		case instCB::SET_5_L: {
			reg_L |= 0b00100000;
		} break;
		case instCB::SET_5_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b00100000;
		} break;
		case instCB::SET_5_A: {
			reg_A |= 0b00100000;
		} break;
			//////////////////////////////////////
		case instCB::SET_6_B: {
			reg_B |= 0b01000000;
		} break;
		case instCB::SET_6_C: {
			reg_C |= 0b01000000;
		} break;
		case instCB::SET_6_D: {
			reg_D |= 0b01000000;
		} break;
		case instCB::SET_6_E: {
			reg_E |= 0b01000000;
		} break;
		case instCB::SET_6_H: {
			reg_H |= 0b01000000;
		} break;
		case instCB::SET_6_L: {
			reg_L |= 0b01000000;
		} break;
		case instCB::SET_6_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b01000000;
		} break;
		case instCB::SET_6_A: {
			reg_A |= 0b01000000;
		} break;
			//////////////////////////////////////
		case instCB::SET_7_B: {
			reg_B |= 0b10000000;
		} break;
		case instCB::SET_7_C: {
			reg_C |= 0b10000000;
		} break;
		case instCB::SET_7_D: {
			reg_D |= 0b10000000;
		} break;
		case instCB::SET_7_E: {
			reg_E |= 0b10000000;
		} break;
		case instCB::SET_7_H: {
			reg_H |= 0b10000000;
		} break;
		case instCB::SET_7_L: {
			reg_L |= 0b10000000;
		} break;
		case instCB::SET_7_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			memory[addr] |= 0b10000000;
		} break;
		case instCB::SET_7_A: {
			reg_A |= 0b10000000;
		} break;
		//////////////////////////////////////
		default:
			break;
		}
	} break;
	case inst::CALL_Z_a16:
		ui(opcode);
	/*
	Description:
		Push address of next instruction onto stack and then
		jump to address nn.
	Use with:
		nn = two byte immediate value. (LS byte first.) */
	case inst::CALL_a16: {
		// Read a16/nn
		uint16_t a16 = read();
		a16 += read() << 8;
		std::cout << "["  << std::hex << a16 << std::dec << "]" << " - CALL_a16";
		// Put pc address onto stack
		memory[--sp] = (uint8_t)pc;
		memory[--sp] = (uint8_t)(pc >> 8);
		// Jump to a16
		pc = a16;
	} break;
	case inst::ADC_A_d8:
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_08H:
	case inst::RET_NC:
	case inst::POP_DE:
	case inst::JP_NC_a16:
	case inst::CALL_NC_a16:
	case inst::PUSH_DE:
	case inst::SUB_d8:
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_10H:
	case inst::RET_C:
	case inst::RETI:
	case inst::JP_C_a16:
	case inst::CALL_C_a16:
	case inst::SBC_A_d8:
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_18H:
		ui(opcode);
	// Store the contents of register A in the internal RAM, port register, 
	// or mode register at the address in the range 0xFF00-0xFFFF specified by 
	// the 8-bit immediate operand a8.
	case inst::LDH_pa8_A: {
		uint8_t addr = read();
		memory[0xFF00 + addr] = reg_A;

		
		// If 0xFF50 is set to non-zero, boot rom is disabled.
		if (!booted && addr == 0x50 && memory[0xFF00 + addr] != 0) {
			booted = true;
			memcpy(memory, cart, cartSize);
			std::cout << std::endl << "BOOTED" << std::endl;
			/////////////////////////////////////////////////////////////////////////// BOOTED
		}
	} break;
	case inst::POP_HL:
		ui(opcode);
	// Store the contents of register A in the internal RAM, port register, 
	// or mode register at the address in the range 0xFF00-0xFFFF specified by register C.
	case inst::LD_pC_A: {
		memory[0xFF00 + reg_C] = reg_A;
	} break;
	case inst::PUSH_HL:
	case inst::AND_a8:
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_20H:
	case inst::ADD_SP_a8:
	case inst::JP_pHL:
		ui(opcode);
	case inst::LD_pa16_A: {
		uint16_t addr = read();
		addr += read() << 8;
		memory[addr] = reg_A;
	} break;
	case inst::XOR_d8:
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_28H:
		ui(opcode);
	/*
	Load into register A the contents of the internal RAM, port register, or mode register 
	at the address in the range 0xFF00-0xFFFF specified by the 8-bit immediate operand a8.
	*/
	case inst::LDH_A_pa8: {
		uint8_t addr = read();
		reg_A = memory[0xFF00 + addr];

	} break;
	case inst::POP_AF: {
		reg_A = memory[sp++];
		reg_F = memory[sp++];
	} break;
	case inst::LD_A_pC:
	case inst::DI:
		ui(opcode);
	case inst::PUSH_AF: {
		// Put register pair BC onto stack
		memory[--sp] = reg_A;
		memory[--sp] = reg_F;
	} break;
	case inst::OR_d8:
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_30H:
	case inst::LD_HL_SPplusr8:
	case inst::LD_SP_HL:
	case inst::LD_A_pa16:
	case inst::EI:
		ui(opcode);
	/*
	Description:
		Compare A with n. This is basically an A - n
		subtraction instruction but the results are thrown
		away.
	Use with:
		n = A,B,C,D,E,H,L,(HL),#
	Flags affected:
		Z - Set if result is zero. (Set if A = n.)
		N - Set.
		H - Set if no borrow from bit 4.
		C - Set for no borrow. (Set if A < n.) */
	case inst::CP_d8: {
		uint8_t d8 = read();
		uint8_t result = reg_A - d8;

		setZFlag(result == 0);
		setNFlag(1);
		setHFlag(!(((reg_A & 0xf) - (d8 & 0xf)) < 0x0));
		setCFlag(reg_A < d8);
	} break;
	/*
	Description:
		Push present address onto stack.
		Jump to address $0000 + n.
	Use with:
		n = $00,$08,$10,$18,$20,$28,$30,$38 */
	case inst::RST_38H: {
		sp--;
		memory[sp] = (uint8_t)(pc >> 8);
		sp--;
		memory[sp] = (uint8_t)pc;
		pc = 0x0000 + 0x38;
	} break;
	default:
		printf("[opcode]: Unknown instruction: %x\n", opcode);
		break;
	}

	std::cout << std::endl;
	return 0;
}
