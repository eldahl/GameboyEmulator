#include "display.h"


display::display(uint8_t* mem) {
	this->memory = mem;

	if (SDL_CreateWindowAndRenderer(800, 600, NULL, &window, &renderer) == -1) {
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	
	SDL_ShowWindow(window);
}

