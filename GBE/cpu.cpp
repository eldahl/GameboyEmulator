#include "cpu.h"
#include <iostream>
#include <bitset>
#include <iomanip>

uint8_t BootDMG[] = {
															//
		0x31,0xfe,0xff,0xaf,0x21,0xff,0x9f,0x32,0xcb,0x7c,0x20,0xfb,0x21,0x26,0xff,0x0e,//
		0x11,0x3e,0x80,0x32,0xe2,0x0c,0x3e,0xf3,0xe2,0x32,0x3e,0x77,0x77,0x3e,0xfc,0xe0,
		0x47,0x11,0x04,0x01,0x21,0x10,0x80,0x1a,0xcd,0x95,0x20,0xcd,0x96,0x20,0x13,0x7b,
		0xfe,0x34,0x20,0xf3,0x11,0xd8,0x20,0x06,0x08,0x1a,0x13,0x22,0x23,0x05,0x20,0xf9,
		0x3e,0x19,0xea,0x10,0x99,0x21,0x2f,0x99,0x0e,0x0c,0x3d,0x28,0x08,0x32,0x0d,0x20,
		0xf9,0x2e,0x0f,0x18,0xf3,0x67,0x3e,0x64,0x57,0xe0,0x42,0x3e,0x91,0xe0,0x40,0x04,
		0x1e,0x02,0x0e,0x0c,0xf0,0x44,0xfe,0x90,0x20,0xfa,0x0d,0x20,0xf7,0x1d,0x20,0xf2,
		0x0e,0x13,0x24,0x7c,0x1e,0x83,0xfe,0x62,0x28,0x06,0x1e,0xc1,0xfe,0x64,0x20,0x06,
		0x7b,0xe2,0x0c,0x3e,0x87,0xe2,0xf0,0x42,0x90,0xe0,0x42,0x15,0x20,0xd2,0x05,0x20,
		0x4f,0x16,0x20,0x18,0xcb,0x4f,0x06,0x04,0xc5,0xcb,0x11,0x17,0xc1,0xcb,0x11,0x17,
		0x05,0x20,0xf5,0x22,0x23,0x22,0x23,0xc9,0xce,0xed,0x66,0x66,0xcc,0x0d,0x20,0x0b,
		0x03,0x73,0x20,0x83,0x20,0x0c,0x20,0x0d,0x20,0x08,0x11,0x1f,0x88,0x89,0x20,0x0e,
		0xdc,0xcc,0x6e,0xe6,0xdd,0xdd,0xd9,0x99,0xbb,0xbb,0x67,0x63,0x6e,0x0e,0xec,0xcc,
		0xdd,0xdc,0x99,0x9f,0xbb,0xb9,0x33,0x3e,0x3c,0x42,0xb9,0xa5,0xb9,0xa5,0x42,0x3c,
		0x21,0x04,0x01,0x11,0xa8,0x20,0x1a,0x13,0xbe,0x20,0xfe,0x23,0x7d,0xfe,0x34,0x20,
		0xf5,0x06,0x19,0x78,0x86,0x23,0x05,0x20,0xfb,0x86,0x20,0xfe,0x3e,0x01,0xe0,0x50
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

uint8_t cpu::read() {

	uint8_t op;
	op = memory[pc];
	pc++;
	return op;
}

void cpu::cycle() {

	if (pc == 0x100)
		return;

	uint8_t op = read();
	opcode(op);
	
}

void ui(uint8_t op) {
	std::cout << std::hex << (int)op << std::endl;
	while (true);
}

int cpu::opcode(uint8_t opcode) 
{
	switch (opcode) {
	case inst::NOP:
	case inst::LD_BC_d16:
	case inst::LD_pBC_A:
	case inst::INC_BC:
	case inst::INC_B:
	case inst::DEC_B:
	case inst::LD_B_d8:
	case inst::RLCA:
	case inst::LD_pa16_SP:
	case inst::ADD_HL_BC:
	case inst::LD_A_pBC:
	case inst::DEC_BC:
		ui(opcode);
	case inst::INC_C: {
		reg_C++;
	} break;
	case inst::DEC_C: {
		reg_C--;
	} break;
	// Load the 8-bit immediate operand d8 into register C.
	case inst::LD_C_d8: {
		reg_C = read();
	} break;
	case inst::RRCA:
	case inst::STOP:
	case inst::LD_DE_d16:
	case inst::LD_pDE_A:
	case inst::INC_DE:
	case inst::INC_D:
	case inst::DEC_D:
	case inst::LD_D_d8:
	case inst::RLA:
	case inst::JR_s8:
	case inst::ADD_HL_DE:
	case inst::LD_A_pDE:
	case inst::DEC_DE:
	case inst::INC_E:
	case inst::DEC_E:
	case inst::LD_E_d8:
	case inst::RRA:
		ui(opcode);
	// If the Z flag is 0, jump s8 steps from the current address stored in the program counter (PC).
	// If not, the instruction following the current JP instruction is executed (as usual).
	case inst::JR_NZ_s8: {
		int s8 = (signed char)read();
		if (((reg_F >> 7) & 0x01) == 0) {
			pc += s8;
			//std::cout << "jumping " << s8 << " steps to address: " << pc << std::endl;
		}
	}
		break;
	case inst::LD_HL_d16: {
		uint16_t temp = read();
		temp += read() << 8;
		reg_H = temp >> 8;
		reg_L = (uint8_t)temp;
	}
		break;
	case inst::LD_pHL_PLUS_A:
	case inst::INC_HL:
	case inst::INC_H:
	case inst::DEC_H:
	case inst::LD_H_d8:
	case inst::DAA:
	case inst::JR_Z_s8:
	case inst::ADD_HL_HL:
	case inst::LD_A_pHL_PLUS:
	case inst::DEC_HL:
	case inst::INC_L:
	case inst::DEC_L:
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
	}
		break;
	// Store the contents of register A into the memory location specified by register pair HL, 
	// and simultaneously decrement the contents of HL.
	case inst::LD_pHL_MINUS_A: {
		uint16_t addr = reg_H << 8 | reg_L;
		memory[addr] = reg_A;
		addr--;
		reg_H = addr >> 8;
		reg_L = (uint8_t)addr;
	}
		break;
	case inst::INC_SP:
	case inst::INC_pHL:
	case inst::DEC_pHL:
	case inst::LD_pHL_d8:
	case inst::SCF:
	case inst::JR_C_r8:
	case inst::ADD_HL_SP:
	case inst::LD_A_pHL_MINUS:
	case inst::DEC_SP:
	case inst::INC_A:
	case inst::DEC_A:
		ui(opcode);
	// Load the 8-bit immediate operand d8 into register A.
	case inst::LD_A_d8:	{
		reg_A = read();
	} break;
	case inst::CCF:
	case inst::LD_B_B:
	case inst::LD_B_C:
	case inst::LD_B_D:
	case inst::LD_B_E:
	case inst::LD_B_H:
	case inst::LD_B_L:
	case inst::LD_B_pHL:
	case inst::LD_B_A:
	case inst::LD_C_B:
	case inst::LD_C_C:
	case inst::LD_C_D:
	case inst::LD_C_E:
	case inst::LD_C_H:
	case inst::LD_C_L:
	case inst::LD_C_pHL:
	case inst::LD_C_A:
	case inst::LD_D_B:
	case inst::LD_D_C:
	case inst::LD_D_D:
	case inst::LD_D_E:
	case inst::LD_D_H:
	case inst::LD_D_L:
	case inst::LD_D_pHL:
	case inst::LD_D_A:
	case inst::LD_E_B:
	case inst::LD_E_C:
	case inst::LD_E_D:
	case inst::LD_E_E:
	case inst::LD_E_H:
	case inst::LD_E_L:
	case inst::LD_E_pHL:
	case inst::LD_E_A:
	case inst::LD_H_B:
	case inst::LD_H_C:
	case inst::LD_H_D:
	case inst::LD_H_E:
	case inst::LD_H_H:
	case inst::LD_H_L:
	case inst::LD_H_pHL:
	case inst::LD_H_A:
	case inst::LD_L_B:
	case inst::LD_L_C:
	case inst::LD_L_D:
	case inst::LD_L_E:
	case inst::LD_L_H:
	case inst::LD_L_L:
	case inst::LD_L_pHL:
	case inst::LD_L_A:
	case inst::LD_pHL_B:
	case inst::LD_pHL_C:
	case inst::LD_pHL_D:
	case inst::LD_pHL_E:
	case inst::LD_pHL_H:
	case inst::LD_pHL_L:
	case inst::HALT:
		ui(opcode);
	// Store the contents of register A in the memory location specified by register pair HL.
	case inst::LD_pHL_A: {
		uint16_t addr = reg_L;
		addr += reg_H << 8;
		memory[addr] = reg_A;
	} break;
	case inst::LD_A_B:
	case inst::LD_A_C:
	case inst::LD_A_D:
	case inst::LD_A_E:
	case inst::LD_A_H:
	case inst::LD_A_L:
	case inst::LD_A_pHL:
	case inst::LD_A_A:
	case inst::ADD_A_B:
	case inst::ADD_A_C:
	case inst::ADD_A_D:
	case inst::ADD_A_E:
	case inst::ADD_A_H:
	case inst::ADD_A_L:
	case inst::ADD_A_pHL:
	case inst::ADD_A_A:
	case inst::ADC_A_B:
	case inst::ADC_A_C:
	case inst::ADC_A_D:
	case inst::ADC_A_E:
	case inst::ADC_A_H:
	case inst::ADC_A_L:
	case inst::ADC_A_pHL:
	case inst::ADC_A_A:
	case inst::SUB_B:
	case inst::SUB_C:
	case inst::SUB_D:
	case inst::SUB_E:
	case inst::SUB_H:
	case inst::SUB_L:
	case inst::SUB_pHL:
	case inst::SUB_A:
	case inst::SBC_A_B:
	case inst::SBC_A_C:
	case inst::SBC_A_D:
	case inst::SBC_A_E:
	case inst::SBC_A_H:
	case inst::SBC_A_L:
	case inst::SBC_A_pHL:
	case inst::SBC_A_A:
	case inst::AND_B:
	case inst::AND_C:
	case inst::AND_D:
	case inst::AND_E:
	case inst::AND_H:
	case inst::AND_L:
	case inst::AND_pHL:
	case inst::AND_A:
	case inst::XOR_B:
	case inst::XOR_C:
	case inst::XOR_D:
	case inst::XOR_E:
	case inst::XOR_H:
	case inst::XOR_L:
		ui(opcode);
	// Take the logical exclusive-OR for each bit of the contents of memory 
	// specified by register pair HL and the contents of register A, 
	// and store the results in register A.
	case inst::XOR_pHL: {
		// Get address
		uint16_t addr = reg_L;
		addr += reg_H << 8;

		uint8_t data = memory[addr];
		reg_A = data ^ reg_A;
	}
		break;
	// Take the logical exclusive-OR for each bit of the contents of register A
	// and the contents of register A, and store the results in register A.
	case inst::XOR_A: {
		reg_A = reg_A ^ reg_A; 
	}
		break;
	case inst::OR_B:
	case inst::OR_C:
	case inst::OR_D:
	case inst::OR_E:
	case inst::OR_H:
	case inst::OR_L:
	case inst::OR_pHL:
	case inst::OR_A:
	case inst::CP_B:
	case inst::CP_C:
	case inst::CP_D:
	case inst::CP_E:
	case inst::CP_H:
	case inst::CP_L:
	case inst::CP_pHL:
	case inst::CP_A:
	case inst::RET_NZ:
	case inst::POP_BC:
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
	case inst::PUSH_BC:
	case inst::ADD_A_d8:
	case inst::RST_00H:
	case inst::RET_Z:
	case inst::RET:
	case inst::JP_Z_a16:
		ui(opcode);
	// CB Prefix instructions
	case inst::PREFIX_CB: {
		uint8_t op = read();
		
		switch (op) {
		case instCB::RLC_B:
		case instCB::RLC_C:
		case instCB::RLC_D:
		case instCB::RLC_E:
		case instCB::RLC_H:
		case instCB::RLC_L:
		case instCB::RLC_pHL:
		case instCB::RLC_A:
			break;
		//////////////////////////////////////
		case instCB::RRC_B:
		case instCB::RRC_C:
		case instCB::RRC_D:
		case instCB::RRC_E:
		case instCB::RRC_H:
		case instCB::RRC_L:
		case instCB::RRC_pHL:
		case instCB::RRC_A:
			break;
		//////////////////////////////////////
		case instCB::RL_B:
		case instCB::RL_C:
		case instCB::RL_D:
		case instCB::RL_E:
		case instCB::RL_H:
		case instCB::RL_L:
		case instCB::RL_pHL:
		case instCB::RL_A:
			break;
		//////////////////////////////////////
		case instCB::RR_B:
		case instCB::RR_C:
		case instCB::RR_D:
		case instCB::RR_E:
		case instCB::RR_H:
		case instCB::RR_L:
		case instCB::RR_pHL:
		case instCB::RR_A:
			break;
		//////////////////////////////////////
		case instCB::SLA_B:
		case instCB::SLA_C:
		case instCB::SLA_D:
		case instCB::SLA_E:
		case instCB::SLA_H:
		case instCB::SLA_L:
		case instCB::SLA_pHL:
		case instCB::SLA_A:
			break;
		//////////////////////////////////////
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
		case instCB::BIT_0_B: {
			uint8_t bit = reg_B & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_C: {
			uint8_t bit = reg_C & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_D: {
			uint8_t bit = reg_D & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_E: {
			uint8_t bit = reg_E & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_H: {
			uint8_t bit = reg_H & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_L: {
			uint8_t bit = reg_L & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_0_A: {
			uint8_t bit = reg_A & 0b00000001;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_1_B: {
			uint8_t bit = reg_B & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_C: {
			uint8_t bit = reg_C & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_D: {
			uint8_t bit = reg_D & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_E: {
			uint8_t bit = reg_E & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_H: {
			uint8_t bit = reg_H & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_L: {
			uint8_t bit = reg_L & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_1_A: {
			uint8_t bit = reg_A & 0b00000010;
			bit = bit >> 1;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_2_B: {
			uint8_t bit = reg_B & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_C: {
			uint8_t bit = reg_C & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_D: {
			uint8_t bit = reg_D & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_E: {
			uint8_t bit = reg_E & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_H: {
			uint8_t bit = reg_H & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_L: {
			uint8_t bit = reg_L & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_2_A: {
			uint8_t bit = reg_A & 0b00000100;
			bit = bit >> 2;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_3_B: {
			uint8_t bit = reg_B & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_C: {
			uint8_t bit = reg_C & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_D: {
			uint8_t bit = reg_D & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_E: {
			uint8_t bit = reg_E & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_H: {
			uint8_t bit = reg_H & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_L: {
			uint8_t bit = reg_L & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_3_A: {
			uint8_t bit = reg_A & 0b00001000;
			bit = bit >> 3;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_4_B: {
			uint8_t bit = reg_B & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_C:{
			uint8_t bit = reg_C & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_D: {
			uint8_t bit = reg_D & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_E: {
			uint8_t bit = reg_E & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_H: {
			uint8_t bit = reg_H & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_L: {
			uint8_t bit = reg_L & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_4_A: {
			uint8_t bit = reg_A & 0b00010000;
			bit = bit >> 4;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_5_B: {
			uint8_t bit = reg_B & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_C: {
			uint8_t bit = reg_C & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_D: {
			uint8_t bit = reg_D & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_E: {
			uint8_t bit = reg_E & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_H: {
			uint8_t bit = reg_H & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_L: {
			uint8_t bit = reg_L & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_5_A: {
			uint8_t bit = reg_A & 0b00100000;
			bit = bit >> 5;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_6_B: {
			uint8_t bit = reg_B & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_C: {
			uint8_t bit = reg_C & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_D: {
			uint8_t bit = reg_D & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_E: {
			uint8_t bit = reg_E & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_H: {
			uint8_t bit = reg_H & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_L: {
			uint8_t bit = reg_L & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_6_A: {
			uint8_t bit = reg_A & 0b01000000;
			bit = bit >> 6;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::BIT_7_B: {
			uint8_t bit = reg_B & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_C: {
			uint8_t bit = reg_C & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_D: {
			uint8_t bit = reg_D & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_E: {
			uint8_t bit = reg_E & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_H: {
			uint8_t bit = reg_H & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_L:
		{
			uint8_t bit = reg_L & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_pHL: {
			uint16_t addr = reg_L;
			addr += reg_H << 8;
			uint8_t bit = memory[addr] & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		case instCB::BIT_7_A: {
			uint8_t bit = reg_A & 0b10000000;
			bit = bit >> 7;
			if (bit)
				reg_F &= ~(bit << 7);
			else
				reg_F |= !bit << 7;
		} break;
		//////////////////////////////////////
		case instCB::RES_0_B:
		case instCB::RES_0_C:
		case instCB::RES_0_D:
		case instCB::RES_0_E:
		case instCB::RES_0_H:
		case instCB::RES_0_L:
		case instCB::RES_0_pHL:
		case instCB::RES_0_A:
			break;
		//////////////////////////////////////
		case instCB::RES_1_B:
		case instCB::RES_1_C:
		case instCB::RES_1_D:
		case instCB::RES_1_E:
		case instCB::RES_1_H:
		case instCB::RES_1_L:
		case instCB::RES_1_pHL:
		case instCB::RES_1_A:
			break;
		//////////////////////////////////////
		case instCB::RES_2_B:
		case instCB::RES_2_C:
		case instCB::RES_2_D:
		case instCB::RES_2_E:
		case instCB::RES_2_H:
		case instCB::RES_2_L:
		case instCB::RES_2_pHL:
		case instCB::RES_2_A:
			break;
		//////////////////////////////////////
		case instCB::RES_3_B:
		case instCB::RES_3_C:
		case instCB::RES_3_D:
		case instCB::RES_3_E:
		case instCB::RES_3_H:
		case instCB::RES_3_L:
		case instCB::RES_3_pHL:
		case instCB::RES_3_A:
			break;
		//////////////////////////////////////
		case instCB::RES_4_B:
		case instCB::RES_4_C:
		case instCB::RES_4_D:
		case instCB::RES_4_E:
		case instCB::RES_4_H:
		case instCB::RES_4_L:
		case instCB::RES_4_pHL:
		case instCB::RES_4_A:
			break;
		//////////////////////////////////////
		case instCB::RES_5_B:
		case instCB::RES_5_C:
		case instCB::RES_5_D:
		case instCB::RES_5_E:
		case instCB::RES_5_H:
		case instCB::RES_5_L:
		case instCB::RES_5_pHL:
		case instCB::RES_5_A:
			break;
		//////////////////////////////////////
		case instCB::RES_6_B:
		case instCB::RES_6_C:
		case instCB::RES_6_D:
		case instCB::RES_6_E:
		case instCB::RES_6_H:
		case instCB::RES_6_L:
		case instCB::RES_6_pHL:
		case instCB::RES_6_A:
			break;
		//////////////////////////////////////
		case instCB::RES_7_B:
		case instCB::RES_7_C:
		case instCB::RES_7_D:
		case instCB::RES_7_E:
		case instCB::RES_7_H:
		case instCB::RES_7_L:
		case instCB::RES_7_pHL:
		case instCB::RES_7_A:
			break;
		//////////////////////////////////////
		case instCB::SET_0_B:
		case instCB::SET_0_C:
		case instCB::SET_0_D:
		case instCB::SET_0_E:
		case instCB::SET_0_H:
		case instCB::SET_0_L:
		case instCB::SET_0_pHL:
		case instCB::SET_0_A:
			break;
		//////////////////////////////////////
		case instCB::SET_1_B:
		case instCB::SET_1_C:
		case instCB::SET_1_D:
		case instCB::SET_1_E:
		case instCB::SET_1_H:
		case instCB::SET_1_L:
		case instCB::SET_1_pHL:
		case instCB::SET_1_A:
			break;
		//////////////////////////////////////
		case instCB::SET_2_B:
		case instCB::SET_2_C:
		case instCB::SET_2_D:
		case instCB::SET_2_E:
		case instCB::SET_2_H:
		case instCB::SET_2_L:
		case instCB::SET_2_pHL:
		case instCB::SET_2_A:
			break;
		//////////////////////////////////////
		case instCB::SET_3_B:
		case instCB::SET_3_C:
		case instCB::SET_3_D:
		case instCB::SET_3_E:
		case instCB::SET_3_H:
		case instCB::SET_3_L:
		case instCB::SET_3_pHL:
		case instCB::SET_3_A:
			break;
		//////////////////////////////////////
		case instCB::SET_4_B:
		case instCB::SET_4_C:
		case instCB::SET_4_D:
		case instCB::SET_4_E:
		case instCB::SET_4_H:
		case instCB::SET_4_L:
		case instCB::SET_4_pHL:
		case instCB::SET_4_A:
			break;
		//////////////////////////////////////
		case instCB::SET_5_B:
		case instCB::SET_5_C:
		case instCB::SET_5_D:
		case instCB::SET_5_E:
		case instCB::SET_5_H:
		case instCB::SET_5_L:
		case instCB::SET_5_pHL:
		case instCB::SET_5_A:
			break;
		//////////////////////////////////////
		case instCB::SET_6_B:
		case instCB::SET_6_C:
		case instCB::SET_6_D:
		case instCB::SET_6_E:
		case instCB::SET_6_H:
		case instCB::SET_6_L:
		case instCB::SET_6_pHL:
		case instCB::SET_6_A:
			break;
		//////////////////////////////////////
		case instCB::SET_7_B:
		case instCB::SET_7_C:
		case instCB::SET_7_D:
		case instCB::SET_7_E:
		case instCB::SET_7_H:
		case instCB::SET_7_L:
		case instCB::SET_7_pHL:
		case instCB::SET_7_A:
			break;
		//////////////////////////////////////
		default:
			break;
		}
	} break;
	case inst::CALL_Z_a16:
	case inst::CALL_a16:
	case inst::ADC_A_d8:
	case inst::RST_08H:
	case inst::RET_NC:
	case inst::POP_DE:
	case inst::JP_NC_a16:
	case inst::CALL_NC_a16:
	case inst::PUSH_DE:
	case inst::SUB_d8:
	case inst::RST_10H:
	case inst::RET_C:
	case inst::RETI:
	case inst::JP_C_a16:
	case inst::CALL_C_a16:
	case inst::SBC_A_d8:
	case inst::RST_18H:
		ui(opcode);
	// Store the contents of register A in the internal RAM, port register, 
	// or mode register at the address in the range 0xFF00-0xFFFF specified by 
	// the 8-bit immediate operand a8.
	case inst::LDH_pa8_A: {
		uint8_t addr = read();
		memory[0xFF00 + addr] = reg_A;

		// If 0xFF50 is set to non-zero, boot rom is disabled.
		if (addr = 0x50 && memory[0xFF00 + addr] != 0) {
			booted = true;
			memcpy(memory, cart, cartSize);
			/////////////////////////////////////////////////////////////////////////// BOOTED
		}
	}
		break;
	case inst::POP_HL:
		ui(opcode);
	// Store the contents of register A in the internal RAM, port register, 
	// or mode register at the address in the range 0xFF00-0xFFFF specified by register C.
	case inst::LD_pC_A: {
		uint8_t addr = reg_C;
		memory[0xFF00 + addr] = reg_A;
	} break;
	case inst::PUSH_HL:
	case inst::AND_a8:
	case inst::RST_20H:
	case inst::ADD_SP_a8:
	case inst::JP_pHL:
	case inst::LD_pa16_A:
	case inst::XOR_d8:
	case inst::RST_28H:
	case inst::LDH_A_pa8:
	case inst::POP_AF:
	case inst::LD_A_pC:
	case inst::DI:
	case inst::PUSH_AF:
	case inst::OR_d8:
	case inst::RST_30H:
	case inst::LD_HL_SPplusr8:
	case inst::LD_SP_HL:
	case inst::LD_A_pa16:
	case inst::EI:
	case inst::CP_d8:
	case inst::RST_38H:
		ui(opcode);

	default:
		printf("[opcode]: Unknown instruction: %x\n", opcode);
		break;
	}

	std::cout << "|" << std::hex << (int)opcode << std::dec << "|";

	return 0;
}
