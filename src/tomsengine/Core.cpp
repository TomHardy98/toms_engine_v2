#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include <GL/glew.h>   // Allows for the use of GLEW

#define WINDOW_WIDTH 1200   // Defining window width
#define WINDOW_HEIGHT 800   // Defining window height

namespace tomsengine
{
	Core::Core()   // Core constructor
	{
		running = false;   // Set running to false

		if (SDL_Init(SDL_INIT_VIDEO) < 0)   // If initialisation of SDL fails
		{
			throw std::exception();   // Throw exception
		}

		window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);   // Create an SDL window

		if (!SDL_GL_CreateContext(window))   // If the window didnt get created
		{
			throw std::exception();   // Throw exception
		}

		if (glewInit() != GLEW_OK)   // If glew didnt initialisation
		{
			throw std::exception();   // Throw exception
		}

		device = alcOpenDevice(NULL);   // Set the device for audio

		if (!device)   // If failed to set device
		{
			throw std::exception();   // Throw exception
		}

		context = alcCreateContext(device, NULL);   // Set context for audio

		if (!context)   // If failed to set context
		{
			alcCloseDevice(device);   // Close the device
			throw std::exception();   // Throw exception
		}

		if (!alcMakeContextCurrent(context))   // If failed to set current context
		{
			alcDestroyContext(context);   // Destroy context
			alcCloseDevice(device);   // Close the device
			throw std::exception();   // Throw exception
		}
	}

	void Core::Start()   // Core start function
	{
		running = true;   // Set running to true

		while (running)   // While running is true
		{
			SDL_Event event = { 0 };   // Create an SDL event array and initialise all to 0

			while (SDL_PollEvent(&event))   // If an event happens
			{
				if (event.type == SDL_QUIT)   // If the event is SDL_QUIT
				{
					running = false;   // Set running to false
				}
			}

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)   // Loop through all the entities
			{
				(*it)->tick();   // Call the tick function for each entity
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set screen colour
			glClear(GL_COLOR_BUFFER_BIT);   // Clear colour buffer

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)   // Loop through all the entities
			{
				(*it)->reveal();   // Call the reveal function for each entity
			}

			SDL_GL_SwapWindow(window);   // Swap the windows
		}
	}

	void Core::Stop()   // Core stop function
	{
		alcMakeContextCurrent(NULL);   // Set context to NULL
		alcDestroyContext(context);   // Destroy context
		alcCloseDevice(device);   // Close the device

		running = false;   // Set running to false
	}

	std::shared_ptr<Entity> Core::addEntity()   // Core addEntity function
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();   // rtn is a shared pointer of Entity
		entities.push_back(rtn);   // Push back rtn on entities vector
		rtn->setTransform();   // Give every entity a transform component
		rtn->self = rtn;   // Set return back
		rtn->core = self;   // Set core back

		return rtn;   // Return rtn
	}
}