#include "display.h"


display::display(uint8_t* mem) {
	this->memory = mem;
	
	window = NULL;
	renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}
	
	if (SDL_CreateWindowAndRenderer(160 * 4, 144 * 4, NULL, &window, &renderer) == -1) {
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	
	SDL_ShowWindow(window);
}

void display::Render() {
	// Clear
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	// Update window
	SDL_RenderPresent(renderer);
}