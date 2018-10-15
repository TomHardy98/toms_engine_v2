#include <memory>
#include <exception>
#include <iostream>
#include <tomsengine/tomsengine.h>
#include <tomsengine/Core.h>

#define shared std::shared_ptr
#define weak std::weak_ptr

void safe_main()
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
}

int main()
{
	try
	{
		safe_main();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	system("PAUSE");

	return 0;
}