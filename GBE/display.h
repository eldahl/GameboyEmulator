#pragma once
#include <cstdint>
#include <SDL.h>
#include <iostream>

class display {

public:
	display(uint8_t* mem);

private:
	uint8_t* memory;

	SDL_Window* window;
	SDL_Renderer* renderer;


};