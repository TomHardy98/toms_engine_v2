#include "Core.h"
#include "Shader.h"

bool Core::Initialize()
{
	int WINDOW_WIDTH = 1200;
	int WINDOW_HEIGHT = 800;

	SDL_Window *window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, 
	SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	// NEED TO FIND IN THE SHADER CLASS WHERE THE FILE IS BEING READ FROM
	std::shared_ptr<Shader> shader;
	shader = std::make_shared<Shader>("data/vertexShader.txt", "data/fragmentShader.txt");

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	return true;
}