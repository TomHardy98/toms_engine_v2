#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "RenderTexture.h"
#include "RTComponent.h"
#include "MeshRenderer.h"
#include "Enemy.h"
#include "Player.h"

#include <GL/glew.h>   // Allows for the use of GLEW
#include <iostream>

#define WINDOW_WIDTH 600  // Defining window width
#define WINDOW_HEIGHT 900   // Defining window height

namespace tomsengine
{
	Core::Core()   // Core constructor
	{
		running = false;   // Set running to false

		if (SDL_Init(SDL_INIT_VIDEO) < 0)   // If initialisation of SDL fails
		{
			throw std::exception();   // Throw exception
		}

		std::cout << "SDL Successfully Initialised" << std::endl;

		window = SDL_CreateWindow("toms_engine_v2", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);   // Create an SDL window

		std::cout << "Window Width Successfully set to " << WINDOW_WIDTH << std::endl;
		std::cout << "Window Height Successfully set to " << WINDOW_HEIGHT << std::endl;


		if (!SDL_GL_CreateContext(window))   // If the window didnt get created
		{
			throw std::exception();   // Throw exception
		}

		std::cout << "Window Successfully Initialised" << std::endl;

		if (glewInit() != GLEW_OK)   // If glew didnt initialisation
		{
			throw std::exception();   // Throw exception
		}

		std::cout << "GLEW Successfully Initialised" << std::endl;

		device = alcOpenDevice(NULL);   // Set the device for audio

		if (!device)   // If failed to set device
		{
			throw std::exception();   // Throw exception
		}

		std::cout << "Device Successfully Initialised" << std::endl;

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

		std::cout << "Audio Device Successfully Initialised" << std::endl;
	}

	void Core::Start(std::shared_ptr<Entity> cam)   // Core start function
	{
		running = true;   // Set running to true

		bool mouseFirst = true;
		bool mouseMotion = false;
		bool moveLeft = false;
		bool moveRight = false;
		bool moveForward = false;
		bool moveBack = false;

		bool isAlive = true;
		int score = 0;

		float mouseRelX = 0.0f;
		float mouseRelY = 0.0f;
		float mouseSense = 0.004f;

		Uint64 now = SDL_GetPerformanceCounter();
		Uint64 last = 0;
		double deltaTs = 0;

		std::cout << "Starting Toms_Engine_V2" << std::endl;

		while (running)   // While running is true
		{
			SDL_Event event = { 0 };   // Create an SDL event array and initialise all to 0

			// Setting up Delta Time
			last = now;
			now = SDL_GetPerformanceCounter();
			deltaTs = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

			if (isAlive)
			{
				score += 1;
				std::cout << "Score: " << score << std::endl;
			}

			while (SDL_PollEvent(&event))   // If an event happens
			{
				if (event.type == SDL_QUIT)   // If the event is SDL_QUIT
				{
					running = false;
				}

				if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						moveForward = true;
						break;
					case SDLK_a:
						moveLeft = true;
						break;
					case SDLK_s:
						moveBack = true;
						break;
					case SDLK_d:
						moveRight = true;
						break;
					}
					break;
				}

				if (event.type == SDL_KEYUP)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						moveForward = false;
						break;
					case SDLK_a:
						moveLeft = false;
						break;
					case SDLK_s:
						moveBack = false;
						break;
					case SDLK_d:
						moveRight = false;
						break;
					}
					break;
				}

				if (isAlive)
				{
					for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
						it != entities.end(); it++)   // Loop through all the entities
					{
						if ((*it)->hasComponent<Player>() == true)
						{
							if (moveForward & !moveBack & !moveLeft & !moveRight)
							{
								if ((*it)->getComponent<Transform>()->getPosition().y >= 16)
								{
									(*it)->getComponent<Transform>()->Translate(0.0f, 0.0f, 0.0f);
								}
								else
								{
									(*it)->getComponent<Transform>()->Translate(0.0f, 0.01f * deltaTs, 0.0f);
									cam->getComponent<Transform>()->Translate(0.0f, 0.01f * deltaTs, 0.0f);
								}
							}

							if (moveBack & !moveForward & !moveLeft & !moveRight)
							{
								if ((*it)->getComponent<Transform>()->getPosition().y <= -6.0f)
								{
									(*it)->getComponent<Transform>()->Translate(0.0f, 0.0f, 0.0f);
								}
								else
								{
									(*it)->getComponent<Transform>()->Translate(0.0f, -0.01f * deltaTs, 0.0f);
									cam->getComponent<Transform>()->Translate(0.0f, -0.01f * deltaTs, 0.0f);
								}
							}

							if (moveLeft & !moveBack & !moveForward & !moveRight)
							{
								if ((*it)->getComponent<Transform>()->getPosition().x <= -11.5f)
								{
									(*it)->getComponent<Transform>()->Translate(0.0f, 0.0f, 0.0f);
								}
								else
								{
									(*it)->getComponent<Transform>()->Translate(-0.01f * deltaTs, 0.0f, 0.0f);
									cam->getComponent<Transform>()->Translate(-0.01f * deltaTs, 0.0f, 0.0f);
								}
							}

							if (moveRight & !moveBack & !moveLeft & !moveForward)
							{
								if ((*it)->getComponent<Transform>()->getPosition().x >= 11.5f)
								{
									(*it)->getComponent<Transform>()->Translate(0.0f, 0.0f, 0.0f);
								}
								else
								{
									(*it)->getComponent<Transform>()->Translate(0.01f * deltaTs, 0.0f, 0.0f);
									cam->getComponent<Transform>()->Translate(0.01f * deltaTs, 0.0f, 0.0f);
								}
							}
						}
					}
				}
				
				// COMMENTED OUT MOUSE MOVEMENT TO ROTATE CAMERA
				/*if (event.type == SDL_MOUSEMOTION) 
				{
					mouseMotion = true;

					if (!mouseFirst) 
					{
						mouseRelX = event.motion.xrel;
						mouseRelY = event.motion.yrel;
					}
					else 
					{
						mouseFirst = false;
						mouseRelX = 0.0f;
						mouseRelY = 0.0f;
					}
				}

				if (mouseMotion)
				{
					mouseMotion = false;
					cam->getComponent<Transform>()->Rotate((mouseRelX * mouseSense), (mouseRelY * mouseSense), 0.0f);
				}*/
			}

			std::vector < std::shared_ptr<Entity>> cameras;

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)   // Loop through all the entities
			{
				if ((*it)->hasComponent<Enemy>() == true)
				{
					(*it)->getComponent<Transform>()->Translate((*it)->getComponent<Transform>()->velocity, 0.0f, 0.0f);

					if (((*it)->getComponent<Transform>()->getPosition().x <= -11.5f && (*it)->getComponent<Transform>()->velocity < 0.0f) || ((*it)->getComponent<Transform>()->getPosition().x >= 11.5f
						&& (*it)->getComponent<Transform>()->velocity > 0.0f))
					{
						(*it)->getComponent<Transform>()->velocity = -(*it)->getComponent<Transform>()->velocity;
					}
				}
			}

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)   // Loop through all the entities
			{
				(*it)->tick();   // Call the tick function for each entity

				if ((*it)->hasComponent<Camera>() == true)
				{
					cameras.push_back(*it);
				}

				for (std::vector<std::shared_ptr<Entity>>::iterator it2 = entities.begin();
					it2 != entities.end(); it2++)   // Loop through all the entities
				{
					if (*it == *it2 || (*it)->hasComponent<BoxCollider>() == false || (*it2)->hasComponent<BoxCollider>() == false)
					{
						continue;
					}
					else
					{
						if ((*it)->getComponent<BoxCollider>()->checkCollisions(*it2) == true)  // Check collisions function
						{
							if ((*it)->hasComponent<Player>() == true || (*it2)->hasComponent<Player>() == true)
							{
								std::cout << "You were Killed by an Asteroid" << std::endl;
								isAlive = false;
								(*it)->getComponent<MeshRenderer>()->isAlive = false;
								(*it2)->getComponent<MeshRenderer>()->isAlive = false;
							}
							else
							{
								continue;
							}
						}
					}
				}
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set screen colour
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear colour buffer and depth buffer
			glEnable(GL_CULL_FACE);

			for (std::vector<std::shared_ptr<Entity> >::iterator it = cameras.begin();
				it != cameras.end(); it++)   // Loop through all the entities
			{
				setCurrCam((*it)->getComponent<Camera>());
			}

			for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
				it != entities.end(); it++)   // Loop through all the entities
			{
				(*it)->reveal();   // Call the reveal function for each entity
			}

			//glDisable(GL_DEPTH_TEST);
			//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


			/*for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
				it != entities.end(); it++)   // Loop through all the entities
			{
				(*it)->postReveal();
			}*/

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
		rtn->core = self;
		rtn->setDefaultTransformPositions();   // Give every entity a transform component
		rtn->self = rtn;   // Set return back

		return rtn;   // Return rtn
	}

	void Core::setCurrCam(std::shared_ptr<Camera> _cam)
	{
		currCam = _cam;
	}

	std::shared_ptr<Camera> Core::getCurrCam()
	{
		return currCam.lock();
	}
}