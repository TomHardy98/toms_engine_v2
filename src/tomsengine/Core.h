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
		Core();   // Initialisation of the core

		void Start();   // Start function for the core

		void Stop();   // Stop function for the core

		std::shared_ptr<Entity> addEntity();   // addEntity function for the core

	private:

		bool running;

		std::vector<std::shared_ptr<Entity>> entities;

		std::weak_ptr<Core> self;

		SDL_Window *window;
	};
}