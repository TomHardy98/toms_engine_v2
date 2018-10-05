#include "Core.h"

bool Core::Initialize()
{
	// Set up OpenGL and SDL inside of here using Lab 3

	int WINDOW_WIDTH = 1200;
	int WINDOW_HEIGHT = 800;

	SDL_Window *window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, 
	SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);



	std::cout << "Hello" << std::endl;
	return true;
}