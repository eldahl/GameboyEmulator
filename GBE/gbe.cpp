#include <iostream>
#include "cpu.h"
#include "cart.h"


bool running = true;

int main(int argc, char* argv[]) {

	cart* _cart = new cart("../tetris.gb");

	cpu* CPU = new cpu(_cart->getRom(), _cart->getRomSize());

	///////////////////

	uint8_t reg_A	= 0b00100000;
	uint8_t d8		= 0000000011;

	//if (((reg_A) & 0xF) == 0x0)
	if (((0b00000) & 0xF) == 0x0)
		std::cout << "Borrow bit 4";

	while (true);
	
	///////////////////

	while (running) {
		CPU->cycle();

	}
	
	return 0;
}