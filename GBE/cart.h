#pragma once
#include <cstdint>
#include <string>


class cart
{
public:
	cart(std::string);
	uint8_t* getRom() { return rom; };
	size_t getRomSize() { return (size_t)romSize; };

private:
	int romSize = 0;
	uint8_t* rom = NULL;


};

