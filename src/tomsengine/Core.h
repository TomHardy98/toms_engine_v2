#include <GL/glew.h>   // Including GLEW
#include <SDL2/SDL.h>   // Including SDL
#include <AL/al.h>
#include <AL/alc.h>

#include <memory>   // Allows for the use of shared and weak pointers
#include <vector>   // Allows for the use of vectors

namespace tomsengine
{
	class Entity;   // Gives access to the Entity class
	class Camera;
	
	class Core : public std::enable_shared_from_this<Core>
	{
	public:
		Core();   // Initialisation of the core

		void Start(std::shared_ptr<Entity> cam);   // Start function for the core

		void Stop();   // Stop function for the core

		std::shared_ptr<Entity> addEntity();   // addEntity function for the core

		void setCurrCam(std::shared_ptr<Camera> _cam);

		std::shared_ptr<Camera> getCurrCam();

		std::shared_ptr<Core> getPtrToThis() { return shared_from_this(); }

		std::shared_ptr<Core> self;   // Weak pointer to point to the core

	private:

		bool running;   // Boolean for if the core is running
		bool isAlive;

		std::vector<std::shared_ptr<Entity>> entities;   // Shared pointer to a vector of entities

		std::vector<std::shared_ptr<Entity>> enemies;

		std::weak_ptr<Camera> currCam;

		ALCdevice* device;   // Represents a hardware device

		ALCcontext* context;

		SDL_Window *window;   // SDL Window for the window
	};
}