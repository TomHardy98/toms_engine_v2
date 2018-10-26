#include "Core.h"
#include "Shader.h"
#include "Entity.h"

// NEED TO FOCUS ON CREATING CES (COMPONENT ENTITY SYSTEM)

namespace tomsengine
{
	Core::Core()
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

		std::shared_ptr<Shader> shader;
		shader = std::make_shared<Shader>("../data/vertexShader.txt", "../data/fragmentShader.txt");

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	void Core::Start()
	{
		running = true;

		while (running)
		{
			SDL_Event event = { 0 };

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
			}

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)
			{
				(*it)->tick();
			}

			glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)
			{
				(*it)->reveal();
			}

			SDL_GL_SwapWindow(window);
		}
	}

	void Core::Stop()
	{
		running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		entities.push_back(rtn);
		rtn->self = rtn;
		rtn->core = self;

		return rtn;
	}
}