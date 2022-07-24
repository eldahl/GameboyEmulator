#include "cart.h"
#include <fstream>
#include <iostream>

cart::cart(std::string romPath) {
	
	printf("Loading ROM... Path: \"%s\"\n", romPath.c_str());

	std::ifstream romStream(romPath, std::ios::binary);

	if (romStream) {
		// Get length
		romStream.seekg(0, romStream.end);
		int length = romStream.tellg();
		romStream.seekg(0, romStream.beg);

		// Create buffer and read content of cartridge
		char* buffer = new char[length];
		romStream.read(buffer, length);

		// Copy into rom memory
		rom = new uint8_t[length];
		for (int i = 0; i < length; i++) {
			rom[i] = (uint8_t)buffer[i];
			//printf("%x", rom[i]);
		}

		romSize = length;

	}
	else
		std::cout << "failed to load rom" << std::endl;

	// Close file handle
	romStream.close();
}