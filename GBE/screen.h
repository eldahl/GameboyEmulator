#pragma once
#include <cstdint>

// Sprite Attribute Table (OAM: Object Attribute Memory)
class oam_entry {
public:
	uint8_t y;
	uint8_t x;
	uint8_t tile;
};

class screen {

public:
	uint8_t reg_LCDC = NULL;

};
