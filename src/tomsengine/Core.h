#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <memory>
#include <vector>

namespace tomsengine
{
	class Entity;
	
	class Core
	{
	public:
		Core();

		void Start();

		void Stop();

		std::shared_ptr<Entity> addEntity();

	private:

		bool running;

		std::vector<std::shared_ptr<Entity>> entities;

		std::weak_ptr<Core> self;

		SDL_Window *window;
	};
}