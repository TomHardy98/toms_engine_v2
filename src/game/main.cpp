#include <memory>
#include <exception>
#include <iostream>
#include <tomsengine/tomsengine.h>

#define shared std::shared_ptr
#define weak std::weak_ptr

using namespace tomsengine;

void safe_main()
{
	// Initialize the engine
	shared<Core> core = std::make_shared<Core>();

	// Create an in-game object
	shared<Entity> entity = core->addEntity();
	/*
	// Add a simple component to it
	weak<TestScreen> testScreen = entity->addComponent<TestScreen>();

	// Start the main engine loop
	core->start();
	*/
}

int main()
{
	safe_main();

	/*try
	{
		safe_main();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}*/

	system("PAUSE");

	return 0;
}