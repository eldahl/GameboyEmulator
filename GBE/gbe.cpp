#include <iostream>
#include "cpu.h"
#include "cart.h"


bool running = true;

int main(int argc, char* argv[]) {

	// Load cartridge
	cart* _cart = new cart("../roms/tetris.gb");

	// Initialize GPU with cartridge
	cpu* CPU = new cpu(_cart->getRom(), _cart->getRomSize());

	while (running) {
		CPU->cycle();

	}
	
	return 0;
}