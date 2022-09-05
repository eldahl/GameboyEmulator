#include <iostream>
#include "cpu.h"
#include "cart.h"
#include <iomanip>
#include <bitset>

bool running = true;

int main(int argc, char* argv[]) {

	cart* _cart = new cart("../tetris.gb");

	cpu* CPU = new cpu(_cart->getRom(), _cart->getRomSize());
	
	while (running) {
		CPU->cycle();

	}
	
	return 0;
}