#include <iostream>
#include <fstream>
#include "cpu.h"
#include "cart.h"
#include "display.h"


bool running = true;

int main(int argc, char* argv[]) {

	std::ofstream out("out.txt");
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	// Load cartridge
	cart* _cart = new cart("../roms/tetris.gb");

	// Initialize GPU with cartridge
	cpu* CPU = new cpu(_cart->getRom(), _cart->getRomSize());

	display* Display = new display(CPU->memory);

	while (running) {
		CPU->cycle();

	}
	
	return 0;
}