#include <memory>
#include <iostream>
#include <tomsengine/tomsengine.h>
#include <tomsengine/Core.h>

#define shared std::shared_ptr
#define weak std::weak_ptr

//using namespace tomsengine;

int main()
{
	
	// Initialize the engine
	shared<Core> core;
	core->Initialize();

    /*// Create an in-game object
	shared<Entity> entity = core->addEntity();
	
	// Add a simple component to it
	weak<TestScreen> testScreen = entity->addComponent<TestScreen>();

	// Start the main engine loop
	core->start();
	*/

	system("PAUSE");

	return 0;
}